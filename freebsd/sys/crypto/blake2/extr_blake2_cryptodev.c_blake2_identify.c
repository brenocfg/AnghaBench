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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
blake2_identify(driver_t *drv, device_t parent)
{

	/* NB: order 10 is so we get attached after h/w devices */
	if (device_find_child(parent, "blaketwo", -1) == NULL &&
	    BUS_ADD_CHILD(parent, 10, "blaketwo", -1) == 0)
		panic("blaketwo: could not attach");
}