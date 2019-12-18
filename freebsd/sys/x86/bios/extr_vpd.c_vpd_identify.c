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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int Length; } ;

/* Variables and functions */
 TYPE_1__* ADDR2VPD (scalar_t__) ; 
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VPD_LEN ; 
 int /*<<< orphan*/  VPD_OFF ; 
 int /*<<< orphan*/  VPD_SIG ; 
 int /*<<< orphan*/  VPD_START ; 
 int /*<<< orphan*/  VPD_STEP ; 
 scalar_t__ bios_sigsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  device_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vpd_identify (driver_t *driver, device_t parent)
{
	device_t child;
	u_int32_t addr;
	int length;
	int rid;

	if (!device_is_alive(parent))
		return;

	addr = bios_sigsearch(VPD_START, VPD_SIG, VPD_LEN, VPD_STEP, VPD_OFF);
	if (addr != 0) {
		rid = 0;
		length = ADDR2VPD(addr)->Length;

		child = BUS_ADD_CHILD(parent, 5, "vpd", -1);
		device_set_driver(child, driver);
		bus_set_resource(child, SYS_RES_MEMORY, rid, addr, length);
		device_set_desc(child, "Vital Product Data Area");
	}
		
	return;
}