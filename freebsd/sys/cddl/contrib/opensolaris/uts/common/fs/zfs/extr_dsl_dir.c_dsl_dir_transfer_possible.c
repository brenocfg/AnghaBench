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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  FALSE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_LIMIT ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_LIMIT ; 
 int /*<<< orphan*/ * closest_common_ancestor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_space_available (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_fs_ss_limit_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  would_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dsl_dir_transfer_possible(dsl_dir_t *sdd, dsl_dir_t *tdd,
    uint64_t fs_cnt, uint64_t ss_cnt, uint64_t space, cred_t *cr)
{
	dsl_dir_t *ancestor;
	int64_t adelta;
	uint64_t avail;
	int err;

	ancestor = closest_common_ancestor(sdd, tdd);
	adelta = would_change(sdd, -space, ancestor);
	avail = dsl_dir_space_available(tdd, ancestor, adelta, FALSE);
	if (avail < space)
		return (SET_ERROR(ENOSPC));

	err = dsl_fs_ss_limit_check(tdd, fs_cnt, ZFS_PROP_FILESYSTEM_LIMIT,
	    ancestor, cr);
	if (err != 0)
		return (err);
	err = dsl_fs_ss_limit_check(tdd, ss_cnt, ZFS_PROP_SNAPSHOT_LIMIT,
	    ancestor, cr);
	if (err != 0)
		return (err);

	return (0);
}