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
struct ofw_compat_data {int dummy; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ofw_compat_data* mpc85xx_jog_devcompat () ; 

__attribute__((used)) static void
mpc85xx_jog_identify(driver_t *driver, device_t parent)
{
	struct ofw_compat_data *compat;

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "mpc85xx_jog", -1) != NULL)
		return;

	compat = mpc85xx_jog_devcompat();
	if (compat == NULL)
		return;
	
	/*
	 * We attach a child for every CPU since settings need to
	 * be performed on every CPU in the SMP case.
	 */
	if (BUS_ADD_CHILD(parent, 10, "jog", -1) == NULL)
		device_printf(parent, "add jog child failed\n");
}