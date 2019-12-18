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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AM335X_CONTROL_BASE ; 
 int /*<<< orphan*/  AM335X_CONTROL_DEVICE_ID ; 
 int /*<<< orphan*/  AM335X_CONTROL_DEV_FEATURE ; 
 int /*<<< orphan*/  AM335X_CONTROL_SIZE ; 
 int AM335X_DEVREV (void*) ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* chip_revision ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  printf (char*,char,int,int) ; 

__attribute__((used)) static void
am335x_get_revision(void)
{
	uint32_t dev_feature;
	char cpu_last_char;
	bus_space_handle_t bsh;
	int major;
	int minor;

	bus_space_map(fdtbus_bs_tag, AM335X_CONTROL_BASE, AM335X_CONTROL_SIZE, 0, &bsh);
	chip_revision = bus_space_read_4(fdtbus_bs_tag, bsh, AM335X_CONTROL_DEVICE_ID);
	dev_feature = bus_space_read_4(fdtbus_bs_tag, bsh, AM335X_CONTROL_DEV_FEATURE);
	bus_space_unmap(fdtbus_bs_tag, bsh, AM335X_CONTROL_SIZE);

	switch (dev_feature) {
		case 0x00FF0382:
			cpu_last_char='2';
			break;
		case 0x20FF0382:
			cpu_last_char='4';
			break;
		case 0x00FF0383:
			cpu_last_char='6';
			break;
		case 0x00FE0383:
			cpu_last_char='7';
			break;
		case 0x20FF0383:
			cpu_last_char='8';
			break;
		case 0x20FE0383:
			cpu_last_char='9';
			break;
		default:
			cpu_last_char='x';
	}

	switch(AM335X_DEVREV(chip_revision)) {
		case 0:
			major = 1;
			minor = 0;
			break;
		case 1:
			major = 2;
			minor = 0;
			break;
		case 2:
			major = 2;
			minor = 1;
			break;
		default:
			major = 0;
			minor = AM335X_DEVREV(chip_revision);
			break;
	}
	printf("Texas Instruments AM335%c Processor, Revision ES%u.%u\n",
		cpu_last_char, major, minor);
}