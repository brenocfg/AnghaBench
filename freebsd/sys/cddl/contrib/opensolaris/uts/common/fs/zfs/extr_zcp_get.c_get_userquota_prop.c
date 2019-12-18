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
typedef  size_t zfs_userquota_prop_t ;

/* Variables and functions */
 size_t ZFS_NUM_USERQUOTA_PROPS ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_userquota_prop_prefixes ; 

__attribute__((used)) static zfs_userquota_prop_t
get_userquota_prop(const char *prop_name)
{
	zfs_userquota_prop_t type;
	/* Figure out the property type ({user|group}{quota|used}) */
	for (type = 0; type < ZFS_NUM_USERQUOTA_PROPS; type++) {
		if (strncmp(prop_name, zfs_userquota_prop_prefixes[type],
		    strlen(zfs_userquota_prop_prefixes[type])) == 0)
			break;
	}
	return (type);
}