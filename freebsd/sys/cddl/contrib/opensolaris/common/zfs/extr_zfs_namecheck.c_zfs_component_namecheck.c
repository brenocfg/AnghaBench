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
 int /*<<< orphan*/  NAME_ERR_EMPTY_COMPONENT ; 
 int /*<<< orphan*/  NAME_ERR_INVALCHAR ; 
 int /*<<< orphan*/  NAME_ERR_TOOLONG ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  valid_char (char const) ; 

int
zfs_component_namecheck(const char *path, namecheck_err_t *why, char *what)
{
	const char *loc;

	if (strlen(path) >= ZFS_MAX_DATASET_NAME_LEN) {
		if (why)
			*why = NAME_ERR_TOOLONG;
		return (-1);
	}

	if (path[0] == '\0') {
		if (why)
			*why = NAME_ERR_EMPTY_COMPONENT;
		return (-1);
	}

	for (loc = path; *loc; loc++) {
		if (!valid_char(*loc)) {
			if (why) {
				*why = NAME_ERR_INVALCHAR;
				*what = *loc;
			}
			return (-1);
		}
	}
	return (0);
}