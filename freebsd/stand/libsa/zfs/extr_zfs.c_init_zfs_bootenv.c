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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zfs_bootenv_initial (char*) ; 

void
init_zfs_bootenv(const char *currdev_in)
{
	char *beroot, *currdev;
	int currdev_len;

	currdev = NULL;
	currdev_len = strlen(currdev_in);
	if (currdev_len == 0)
		return;
	if (strncmp(currdev_in, "zfs:", 4) != 0)
		return;
	currdev = strdup(currdev_in);
	if (currdev == NULL)
		return;
	/* Remove the trailing : */
	currdev[currdev_len - 1] = '\0';
	setenv("zfs_be_active", currdev, 1);
	setenv("zfs_be_currpage", "1", 1);
	/* Remove the last element (current bootenv) */
	beroot = strrchr(currdev, '/');
	if (beroot != NULL)
		beroot[0] = '\0';
	beroot = strchr(currdev, ':') + 1;
	setenv("zfs_be_root", beroot, 1);
	zfs_bootenv_initial(beroot);
	free(currdev);
}