#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct nxp_74hc153_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nxp_74hc153_platform_data {int /*<<< orphan*/  gpio_pin_s0; int /*<<< orphan*/  gpio_pin_s1; int /*<<< orphan*/  gpio_pin_1y; int /*<<< orphan*/  gpio_pin_2y; } ;
struct nxp_74hc153_chip {int /*<<< orphan*/  gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nxp_74hc153_chip*) ; 
 struct nxp_74hc153_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nxp_74hc153_remove(struct platform_device *pdev)
{
	struct nxp_74hc153_chip *nxp = platform_get_drvdata(pdev);
	struct nxp_74hc153_platform_data *pdata = pdev->dev.platform_data;

	if (nxp) {
		gpiochip_remove(&nxp->gpio_chip);
		gpio_free(pdata->gpio_pin_2y);
		gpio_free(pdata->gpio_pin_1y);
		gpio_free(pdata->gpio_pin_s1);
		gpio_free(pdata->gpio_pin_s0);

		kfree(nxp);
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}