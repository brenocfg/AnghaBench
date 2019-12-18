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
 char const* _PATH_FSTAB ; 
 scalar_t__ fsp_set ; 
 char const* path_fstab ; 

const char *
getfstab(void)
{

	if (fsp_set)
		return (path_fstab);
	else
		return (_PATH_FSTAB);
}