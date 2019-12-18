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
struct bootinfo {int bi_boot_dev_type; } ;

/* Variables and functions */
#define  BOOTINFO_DEV_TYPE_CFI 130 
#define  BOOTINFO_DEV_TYPE_DRAM 129 
#define  BOOTINFO_DEV_TYPE_SDCARD 128 
 int /*<<< orphan*/  EV_VOLATILE ; 
 int /*<<< orphan*/ * env_noset ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extract_currdev(struct bootinfo *bootinfop)
{
	const char *bootdev;

	/*
	 * Pick up boot device information from boot2.
	 *
	 * XXXRW: Someday: device units.
	 */
	switch(bootinfop->bi_boot_dev_type) {
	case BOOTINFO_DEV_TYPE_DRAM:
		bootdev = "dram0";
		break;

	case BOOTINFO_DEV_TYPE_CFI:
		bootdev = "cfi0";
		break;

	case BOOTINFO_DEV_TYPE_SDCARD:
		bootdev = "sdcard0";
		break;

	default:
		bootdev = NULL;
	}

	if (bootdev != NULL) {
		env_setenv("currdev", EV_VOLATILE, bootdev, NULL, env_nounset);
		env_setenv("loaddev", EV_VOLATILE, bootdev, env_noset,
		    env_nounset);
	}
}