#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;
struct cht_wc_extcon_data {TYPE_1__* dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  edev; int /*<<< orphan*/  previous_cable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_PWRSRC_IRQ_MASK ; 
 unsigned long CHT_WC_PWRSRC_USBID_MASK ; 
 unsigned long CHT_WC_PWRSRC_VBUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTCON_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUX_SEL_PMIC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cht_wc_extcon_cables ; 
 int /*<<< orphan*/  cht_wc_extcon_enable_charging (struct cht_wc_extcon_data*,int) ; 
 int /*<<< orphan*/  cht_wc_extcon_isr ; 
 int /*<<< orphan*/  cht_wc_extcon_pwrsrc_event (struct cht_wc_extcon_data*) ; 
 int /*<<< orphan*/  cht_wc_extcon_set_5v_boost (struct cht_wc_extcon_data*,int) ; 
 int /*<<< orphan*/  cht_wc_extcon_set_phymux (struct cht_wc_extcon_data*,int /*<<< orphan*/ ) ; 
 int cht_wc_extcon_sw_control (struct cht_wc_extcon_data*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct cht_wc_extcon_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cht_wc_extcon_data*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cht_wc_extcon_data*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int cht_wc_extcon_probe(struct platform_device *pdev)
{
	struct intel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	struct cht_wc_extcon_data *ext;
	unsigned long mask = ~(CHT_WC_PWRSRC_VBUS | CHT_WC_PWRSRC_USBID_MASK);
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ext = devm_kzalloc(&pdev->dev, sizeof(*ext), GFP_KERNEL);
	if (!ext)
		return -ENOMEM;

	ext->dev = &pdev->dev;
	ext->regmap = pmic->regmap;
	ext->previous_cable = EXTCON_NONE;

	/* Initialize extcon device */
	ext->edev = devm_extcon_dev_allocate(ext->dev, cht_wc_extcon_cables);
	if (IS_ERR(ext->edev))
		return PTR_ERR(ext->edev);

	/*
	 * When a host-cable is detected the BIOS enables an external 5v boost
	 * converter to power connected devices there are 2 problems with this:
	 * 1) This gets seen by the external battery charger as a valid Vbus
	 *    supply and it then tries to feed Vsys from this creating a
	 *    feedback loop which causes aprox. 300 mA extra battery drain
	 *    (and unless we drive the external-charger-disable pin high it
	 *    also tries to charge the battery causing even more feedback).
	 * 2) This gets seen by the pwrsrc block as a SDP USB Vbus supply
	 * Since the external battery charger has its own 5v boost converter
	 * which does not have these issues, we simply turn the separate
	 * external 5v boost converter off and leave it off entirely.
	 */
	cht_wc_extcon_set_5v_boost(ext, false);

	/* Enable sw control */
	ret = cht_wc_extcon_sw_control(ext, true);
	if (ret)
		goto disable_sw_control;

	/* Disable charging by external battery charger */
	cht_wc_extcon_enable_charging(ext, false);

	/* Register extcon device */
	ret = devm_extcon_dev_register(ext->dev, ext->edev);
	if (ret) {
		dev_err(ext->dev, "Error registering extcon device: %d\n", ret);
		goto disable_sw_control;
	}

	/* Route D+ and D- to PMIC for initial charger detection */
	cht_wc_extcon_set_phymux(ext, MUX_SEL_PMIC);

	/* Get initial state */
	cht_wc_extcon_pwrsrc_event(ext);

	ret = devm_request_threaded_irq(ext->dev, irq, NULL, cht_wc_extcon_isr,
					IRQF_ONESHOT, pdev->name, ext);
	if (ret) {
		dev_err(ext->dev, "Error requesting interrupt: %d\n", ret);
		goto disable_sw_control;
	}

	/* Unmask irqs */
	ret = regmap_write(ext->regmap, CHT_WC_PWRSRC_IRQ_MASK, mask);
	if (ret) {
		dev_err(ext->dev, "Error writing irq-mask: %d\n", ret);
		goto disable_sw_control;
	}

	platform_set_drvdata(pdev, ext);

	return 0;

disable_sw_control:
	cht_wc_extcon_sw_control(ext, false);
	return ret;
}