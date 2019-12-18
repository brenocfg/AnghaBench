#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_INVALIDNAME ; 
 int BE_ERR_NOENT ; 
 int BE_ERR_PATHLEN ; 
 int BE_ERR_SUCCESS ; 
 scalar_t__ BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_name_valid (char const*,int /*<<< orphan*/ ) ; 

int
be_validate_snap(libbe_handle_t *lbh, const char *snap_name)
{

	if (strlen(snap_name) >= BE_MAXPATHLEN)
		return (BE_ERR_PATHLEN);

	if (!zfs_name_valid(snap_name, ZFS_TYPE_SNAPSHOT))
		return (BE_ERR_INVALIDNAME);

	if (!zfs_dataset_exists(lbh->lzh, snap_name,
	    ZFS_TYPE_SNAPSHOT))
		return (BE_ERR_NOENT);

	return (BE_ERR_SUCCESS);
}