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
typedef  int /*<<< orphan*/  namecheck_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_ERR_NO_AT ; 
 int /*<<< orphan*/  NAME_ERR_TOOLONG ; 
 scalar_t__ ZFS_PERMSET_MAXLEN ; 
 scalar_t__ strlen (char const*) ; 
 int zfs_component_namecheck (char const*,int /*<<< orphan*/ *,char*) ; 

int
permset_namecheck(const char *path, namecheck_err_t *why, char *what)
{
	if (strlen(path) >= ZFS_PERMSET_MAXLEN) {
		if (why)
			*why = NAME_ERR_TOOLONG;
		return (-1);
	}

	if (path[0] != '@') {
		if (why) {
			*why = NAME_ERR_NO_AT;
			*what = path[0];
		}
		return (-1);
	}

	return (zfs_component_namecheck(&path[1], why, what));
}