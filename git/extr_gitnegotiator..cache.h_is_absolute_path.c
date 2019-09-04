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
 scalar_t__ has_dos_drive_prefix (char const*) ; 
 scalar_t__ is_dir_sep (char const) ; 

__attribute__((used)) static inline int is_absolute_path(const char *path)
{
	return is_dir_sep(path[0]) || has_dos_drive_prefix(path);
}