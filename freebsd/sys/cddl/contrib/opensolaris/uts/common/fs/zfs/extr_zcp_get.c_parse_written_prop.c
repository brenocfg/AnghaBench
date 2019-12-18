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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ZFS_WRITTEN_PROP_PREFIX_LEN ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  zfs_prop_written (char const*) ; 

__attribute__((used)) static void
parse_written_prop(const char *dataset_name, const char *prop_name,
    char *snap_name)
{
	ASSERT(zfs_prop_written(prop_name));
	const char *name = prop_name + ZFS_WRITTEN_PROP_PREFIX_LEN;
	if (strchr(name, '@') == NULL) {
		(void) sprintf(snap_name, "%s@%s", dataset_name, name);
	} else {
		(void) strcpy(snap_name, name);
	}
}