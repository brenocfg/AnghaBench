#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_NOENT ; 
 int BE_ERR_SUCCESS ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  be_root_concat (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
be_exists(libbe_handle_t *lbh, char *be)
{
	char buf[BE_MAXPATHLEN];

	be_root_concat(lbh, be, buf);

	if (!zfs_dataset_exists(lbh->lzh, buf, ZFS_TYPE_DATASET))
		return (BE_ERR_NOENT);

	return (BE_ERR_SUCCESS);
}