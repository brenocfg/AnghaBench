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
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 TYPE_1__* ADDR2HDR (scalar_t__) ; 
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SMAPI_LEN ; 
 int /*<<< orphan*/  SMAPI_OFF ; 
 int /*<<< orphan*/  SMAPI_SIG ; 
 int /*<<< orphan*/  SMAPI_START ; 
 int /*<<< orphan*/  SMAPI_STEP ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bios_sigsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  device_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smapi_identify (driver_t *driver, device_t parent)
{
	device_t child;
	u_int32_t addr;
	int length;
	int rid;

	if (!device_is_alive(parent))
		return;

	addr = bios_sigsearch(SMAPI_START, SMAPI_SIG, SMAPI_LEN,
                              SMAPI_STEP, SMAPI_OFF);
	if (addr != 0) {
		rid = 0;
		length = ADDR2HDR(addr)->length;

		child = BUS_ADD_CHILD(parent, 5, "smapi", -1);
		device_set_driver(child, driver);
		bus_set_resource(child, SYS_RES_MEMORY, rid, addr, length);
		device_set_desc(child, "SMAPI BIOS");
	}

	return;
}