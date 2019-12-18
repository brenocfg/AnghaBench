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
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  xen_domain () ; 

__attribute__((used)) static void
gntdev_identify(driver_t *driver, device_t parent)
{

	KASSERT((xen_domain()),
	    ("Trying to attach gntdev device on non Xen domain"));

	if (BUS_ADD_CHILD(parent, 0, "gntdev", 0) == NULL)
		panic("unable to attach gntdev user-space device");
}