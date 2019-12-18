#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bcm_device {int res_enabled; int (* set_shutdown ) (struct bcm_device*,int) ;int (* set_device_wakeup ) (struct bcm_device*,int) ;TYPE_1__* supplies; int /*<<< orphan*/  lpo_clk; int /*<<< orphan*/  txco_clk; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub1 (struct bcm_device*,int) ; 
 int stub2 (struct bcm_device*,int) ; 
 int stub3 (struct bcm_device*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bcm_gpio_set_power(struct bcm_device *dev, bool powered)
{
	int err;

	if (powered && !dev->res_enabled) {
		/* Intel Macs use bcm_apple_get_resources() and don't
		 * have regulator supplies configured.
		 */
		if (dev->supplies[0].supply) {
			err = regulator_bulk_enable(BCM_NUM_SUPPLIES,
						    dev->supplies);
			if (err)
				return err;
		}

		/* LPO clock needs to be 32.768 kHz */
		err = clk_set_rate(dev->lpo_clk, 32768);
		if (err) {
			dev_err(dev->dev, "Could not set LPO clock rate\n");
			goto err_regulator_disable;
		}

		err = clk_prepare_enable(dev->lpo_clk);
		if (err)
			goto err_regulator_disable;

		err = clk_prepare_enable(dev->txco_clk);
		if (err)
			goto err_lpo_clk_disable;
	}

	err = dev->set_shutdown(dev, powered);
	if (err)
		goto err_txco_clk_disable;

	err = dev->set_device_wakeup(dev, powered);
	if (err)
		goto err_revert_shutdown;

	if (!powered && dev->res_enabled) {
		clk_disable_unprepare(dev->txco_clk);
		clk_disable_unprepare(dev->lpo_clk);

		/* Intel Macs use bcm_apple_get_resources() and don't
		 * have regulator supplies configured.
		 */
		if (dev->supplies[0].supply)
			regulator_bulk_disable(BCM_NUM_SUPPLIES,
					       dev->supplies);
	}

	/* wait for device to power on and come out of reset */
	usleep_range(100000, 120000);

	dev->res_enabled = powered;

	return 0;

err_revert_shutdown:
	dev->set_shutdown(dev, !powered);
err_txco_clk_disable:
	if (powered && !dev->res_enabled)
		clk_disable_unprepare(dev->txco_clk);
err_lpo_clk_disable:
	if (powered && !dev->res_enabled)
		clk_disable_unprepare(dev->lpo_clk);
err_regulator_disable:
	if (powered && !dev->res_enabled)
		regulator_bulk_disable(BCM_NUM_SUPPLIES, dev->supplies);
	return err;
}