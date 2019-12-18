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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  BOOTINFO_DEV_TYPE_DRAM 128 
 int /*<<< orphan*/  boot_fromdram () ; 
 int /*<<< orphan*/  boot_fromfs () ; 
 TYPE_1__ dsk ; 

__attribute__((used)) static void
load(void)
{

	switch (dsk.type) {
	case BOOTINFO_DEV_TYPE_DRAM:
		boot_fromdram();
		break;

	default:
		boot_fromfs();
		break;
	}
}