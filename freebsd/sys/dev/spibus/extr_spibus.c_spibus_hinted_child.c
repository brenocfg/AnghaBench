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
struct spibus_ivar {int /*<<< orphan*/  mode; int /*<<< orphan*/  cs; int /*<<< orphan*/  clock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 struct spibus_ivar* SPIBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIBUS_MODE_NONE ; 
 int /*<<< orphan*/  resource_int_value (char const*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spibus_hinted_child(device_t bus, const char *dname, int dunit)
{
	device_t child;
	struct spibus_ivar *devi;

	child = BUS_ADD_CHILD(bus, 0, dname, dunit);
	devi = SPIBUS_IVAR(child);
	devi->mode = SPIBUS_MODE_NONE;
	resource_int_value(dname, dunit, "clock", &devi->clock);
	resource_int_value(dname, dunit, "cs", &devi->cs);
	resource_int_value(dname, dunit, "mode", &devi->mode);
}