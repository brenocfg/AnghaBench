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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ mdio_driver ; 

__attribute__((used)) static void
mdio_identify(driver_t *driver, device_t parent)
{

	if (device_find_child(parent, mdio_driver.name, -1) == NULL)
		BUS_ADD_CHILD(parent, 0, mdio_driver.name, -1);
}