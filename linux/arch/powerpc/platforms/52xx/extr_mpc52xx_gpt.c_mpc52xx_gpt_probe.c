#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mpc52xx_gpt_priv {TYPE_1__* dev; int /*<<< orphan*/  wdt_mode; int /*<<< orphan*/  list; int /*<<< orphan*/  regs; int /*<<< orphan*/  ipb_freq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPC52xx_GPT_CAN_WDT ; 
 int /*<<< orphan*/  MPC52xx_GPT_IS_WDT ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct mpc52xx_gpt_priv*) ; 
 struct mpc52xx_gpt_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc52xx_gpt_gpio_setup (struct mpc52xx_gpt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_gpt_irq_setup (struct mpc52xx_gpt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_gpt_list ; 
 int /*<<< orphan*/  mpc52xx_gpt_list_mutex ; 
 int /*<<< orphan*/  mpc52xx_gpt_wdt_setup (struct mpc52xx_gpt_priv*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpc5xxx_get_bus_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc52xx_gpt_probe(struct platform_device *ofdev)
{
	struct mpc52xx_gpt_priv *gpt;

	gpt = devm_kzalloc(&ofdev->dev, sizeof *gpt, GFP_KERNEL);
	if (!gpt)
		return -ENOMEM;

	raw_spin_lock_init(&gpt->lock);
	gpt->dev = &ofdev->dev;
	gpt->ipb_freq = mpc5xxx_get_bus_frequency(ofdev->dev.of_node);
	gpt->regs = of_iomap(ofdev->dev.of_node, 0);
	if (!gpt->regs)
		return -ENOMEM;

	dev_set_drvdata(&ofdev->dev, gpt);

	mpc52xx_gpt_gpio_setup(gpt, ofdev->dev.of_node);
	mpc52xx_gpt_irq_setup(gpt, ofdev->dev.of_node);

	mutex_lock(&mpc52xx_gpt_list_mutex);
	list_add(&gpt->list, &mpc52xx_gpt_list);
	mutex_unlock(&mpc52xx_gpt_list_mutex);

	/* check if this device could be a watchdog */
	if (of_get_property(ofdev->dev.of_node, "fsl,has-wdt", NULL) ||
	    of_get_property(ofdev->dev.of_node, "has-wdt", NULL)) {
		const u32 *on_boot_wdt;

		gpt->wdt_mode = MPC52xx_GPT_CAN_WDT;
		on_boot_wdt = of_get_property(ofdev->dev.of_node,
					      "fsl,wdt-on-boot", NULL);
		if (on_boot_wdt) {
			dev_info(gpt->dev, "used as watchdog\n");
			gpt->wdt_mode |= MPC52xx_GPT_IS_WDT;
		} else
			dev_info(gpt->dev, "can function as watchdog\n");
		mpc52xx_gpt_wdt_setup(gpt, on_boot_wdt);
	}

	return 0;
}