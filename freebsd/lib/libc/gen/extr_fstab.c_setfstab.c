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
 int PATH_MAX ; 
 char* _PATH_FSTAB ; 
 int fsp_set ; 
 char* fstab_path ; 
 char* path_fstab ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void
setfstab(const char *file)
{

	if (file == NULL) {
		path_fstab = _PATH_FSTAB;
	} else {
		strncpy(fstab_path, file, PATH_MAX);
		fstab_path[PATH_MAX - 1] = '\0';
		path_fstab = fstab_path;
	}
	fsp_set = 1;

	return;
}