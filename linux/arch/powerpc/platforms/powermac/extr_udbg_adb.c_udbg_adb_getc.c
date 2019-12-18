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

/* Variables and functions */
 scalar_t__ input_adb_none ; 
 scalar_t__ input_type ; 
 int udbg_adb_local_getc () ; 
 int udbg_adb_old_getc () ; 
 scalar_t__ udbg_adb_use_btext ; 

__attribute__((used)) static int udbg_adb_getc(void)
{
#ifdef CONFIG_BOOTX_TEXT
	if (udbg_adb_use_btext && input_type != input_adb_none)
		return udbg_adb_local_getc();
#endif
	if (udbg_adb_old_getc)
		return udbg_adb_old_getc();
	return -1;
}