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
 int /*<<< orphan*/  NAME_ERR_LEADING_SLASH ; 
 int /*<<< orphan*/  NAME_ERR_TOOLONG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 

int
mountpoint_namecheck(const char *path, namecheck_err_t *why)
{
	const char *start, *end;

	/*
	 * Make sure none of the mountpoint component names are too long.
	 * If a component name is too long then the mkdir of the mountpoint
	 * will fail but then the mountpoint property will be set to a value
	 * that can never be mounted.  Better to fail before setting the prop.
	 * Extra slashes are OK, they will be tossed by the mountpoint mkdir.
	 */

	if (path == NULL || *path != '/') {
		if (why)
			*why = NAME_ERR_LEADING_SLASH;
		return (-1);
	}

	/* Skip leading slash  */
	start = &path[1];
	do {
		end = start;
		while (*end != '/' && *end != '\0')
			end++;

		if (end - start >= ZFS_MAX_DATASET_NAME_LEN) {
			if (why)
				*why = NAME_ERR_TOOLONG;
			return (-1);
		}
		start = end + 1;

	} while (*end != '\0');

	return (0);
}