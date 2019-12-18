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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int length; int major_version; int minor_version; } ;

/* Variables and functions */
 TYPE_1__* ADDR2EPS (scalar_t__) ; 
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SMBIOS_LEN ; 
 int /*<<< orphan*/  SMBIOS_OFF ; 
 int /*<<< orphan*/  SMBIOS_SIG ; 
 int /*<<< orphan*/  SMBIOS_START ; 
 int /*<<< orphan*/  SMBIOS_STEP ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bios_sigsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  device_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smbios_identify (driver_t *driver, device_t parent)
{
	device_t child;
	u_int32_t addr;
	int length;
	int rid;

	if (!device_is_alive(parent))
		return;

	addr = bios_sigsearch(SMBIOS_START, SMBIOS_SIG, SMBIOS_LEN,
			      SMBIOS_STEP, SMBIOS_OFF);
	if (addr != 0) {
		rid = 0;
		length = ADDR2EPS(addr)->length;

		if (length != 0x1f) {
			u_int8_t major, minor;

			major = ADDR2EPS(addr)->major_version;
			minor = ADDR2EPS(addr)->minor_version;

			/* SMBIOS v2.1 implementation might use 0x1e. */
			if (length == 0x1e && major == 2 && minor == 1)
				length = 0x1f;
			else
				return;
		}

		child = BUS_ADD_CHILD(parent, 5, "smbios", -1);
		device_set_driver(child, driver);
		bus_set_resource(child, SYS_RES_MEMORY, rid, addr, length);
		device_set_desc(child, "System Management BIOS");
	}

	return;
}