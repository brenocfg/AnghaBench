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
 scalar_t__ is_dir_sep (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static void strip_trailing_slashes(char *dir)
{
	char *end = dir + strlen(dir);

	while (dir < end - 1 && is_dir_sep(end[-1]))
		end--;
	*end = '\0';
}