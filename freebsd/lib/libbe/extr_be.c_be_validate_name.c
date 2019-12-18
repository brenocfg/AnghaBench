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
struct TYPE_3__ {char const* root; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_INVALIDNAME ; 
 int BE_ERR_PATHLEN ; 
 int BE_ERR_SUCCESS ; 
 scalar_t__ MAXNAMELEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zfs_name_valid (char const*,int /*<<< orphan*/ ) ; 

int
be_validate_name(libbe_handle_t *lbh, const char *name)
{

	/*
	 * Impose the additional restriction that the entire dataset name must
	 * not exceed the maximum length of a dataset, i.e. MAXNAMELEN.
	 */
	if (strlen(lbh->root) + 1 + strlen(name) > MAXNAMELEN)
		return (BE_ERR_PATHLEN);

	if (!zfs_name_valid(name, ZFS_TYPE_DATASET))
		return (BE_ERR_INVALIDNAME);

	return (BE_ERR_SUCCESS);
}