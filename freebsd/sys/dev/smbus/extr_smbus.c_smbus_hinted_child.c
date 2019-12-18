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
struct smbus_ivar {int addr; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  SMBUS_ORDER_HINTED ; 
 int UINT8_MAX ; 
 struct smbus_ivar* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,char const*,int) ; 
 int /*<<< orphan*/  resource_int_value (char const*,int,char*,int*) ; 

__attribute__((used)) static void
smbus_hinted_child(device_t bus, const char *dname, int dunit)
{
	struct smbus_ivar *devi;
	device_t child;
	int addr;

	addr = 0;
	resource_int_value(dname, dunit, "addr", &addr);
	if (addr > UINT8_MAX) {
		device_printf(bus, "ignored incorrect slave address hint 0x%x"
		    " for %s%d\n", addr, dname, dunit);
		return;
	}
	child = BUS_ADD_CHILD(bus, SMBUS_ORDER_HINTED, dname, dunit);
	if (child == NULL)
		return;
	devi = device_get_ivars(child);
	devi->addr = addr;
}