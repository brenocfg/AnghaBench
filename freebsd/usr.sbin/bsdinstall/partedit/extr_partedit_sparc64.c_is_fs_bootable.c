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
 scalar_t__ strcmp (char const*,char*) ; 

int
is_fs_bootable(const char *part_type, const char *fs)
{
	if (strcmp(fs, "freebsd-ufs") == 0 || strcmp(fs, "freebsd-zfs") == 0)
		return (1);
	return (0);
}