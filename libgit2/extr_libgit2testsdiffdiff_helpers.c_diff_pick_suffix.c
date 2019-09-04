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
 scalar_t__ GIT_PERMS_IS_EXEC (int) ; 
 scalar_t__ S_ISDIR (int) ; 

__attribute__((used)) static char diff_pick_suffix(int mode)
{
	if (S_ISDIR(mode))
		return '/';
	else if (GIT_PERMS_IS_EXEC(mode))
		return '*';
	else
		return ' ';
}