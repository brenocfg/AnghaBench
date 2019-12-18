#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_device {scalar_t__ irq; struct gpio_desc* reset; int /*<<< orphan*/  list; struct platform_device* pdev; int /*<<< orphan*/  hu_lock; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_hci_intel_gpios ; 
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_wakeup_disable (int /*<<< orphan*/ *) ; 
 int devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct intel_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  intel_device_list ; 
 int /*<<< orphan*/  intel_device_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_device*) ; 

__attribute__((used)) static int intel_probe(struct platform_device *pdev)
{
	struct intel_device *idev;
	int ret;

	idev = devm_kzalloc(&pdev->dev, sizeof(*idev), GFP_KERNEL);
	if (!idev)
		return -ENOMEM;

	mutex_init(&idev->hu_lock);

	idev->pdev = pdev;

	ret = devm_acpi_dev_add_driver_gpios(&pdev->dev, acpi_hci_intel_gpios);
	if (ret)
		dev_dbg(&pdev->dev, "Unable to add GPIO mapping table\n");

	idev->reset = devm_gpiod_get(&pdev->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(idev->reset)) {
		dev_err(&pdev->dev, "Unable to retrieve gpio\n");
		return PTR_ERR(idev->reset);
	}

	idev->irq = platform_get_irq(pdev, 0);
	if (idev->irq < 0) {
		struct gpio_desc *host_wake;

		dev_err(&pdev->dev, "No IRQ, falling back to gpio-irq\n");

		host_wake = devm_gpiod_get(&pdev->dev, "host-wake", GPIOD_IN);
		if (IS_ERR(host_wake)) {
			dev_err(&pdev->dev, "Unable to retrieve IRQ\n");
			goto no_irq;
		}

		idev->irq = gpiod_to_irq(host_wake);
		if (idev->irq < 0) {
			dev_err(&pdev->dev, "No corresponding irq for gpio\n");
			goto no_irq;
		}
	}

	/* Only enable wake-up/irq when controller is powered */
	device_set_wakeup_capable(&pdev->dev, true);
	device_wakeup_disable(&pdev->dev);

no_irq:
	platform_set_drvdata(pdev, idev);

	/* Place this instance on the device list */
	mutex_lock(&intel_device_list_lock);
	list_add_tail(&idev->list, &intel_device_list);
	mutex_unlock(&intel_device_list_lock);

	dev_info(&pdev->dev, "registered, gpio(%d)/irq(%d).\n",
		 desc_to_gpio(idev->reset), idev->irq);

	return 0;
}