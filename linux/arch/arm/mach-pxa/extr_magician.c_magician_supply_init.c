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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPIO_MAGICIAN_CABLE_INSERTED ; 
 int /*<<< orphan*/  EGPIO_MAGICIAN_CABLE_TYPE ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int magician_supply_init(struct device *dev)
{
	int ret = -1;

	ret = gpio_request(EGPIO_MAGICIAN_CABLE_TYPE, "Cable is AC charger");
	if (ret) {
		pr_err("Cannot request AC/USB charger GPIO (%i)\n", ret);
		goto err_ac;
	}

	ret = gpio_request(EGPIO_MAGICIAN_CABLE_INSERTED, "Cable inserted");
	if (ret) {
		pr_err("Cannot request cable detection GPIO (%i)\n", ret);
		goto err_usb;
	}

	return 0;

err_usb:
	gpio_free(EGPIO_MAGICIAN_CABLE_TYPE);
err_ac:
	return ret;
}