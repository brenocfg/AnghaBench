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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ FUID_INDEX (scalar_t__) ; 

__attribute__((used)) static int
zfs_replay_domain_cnt(uint64_t uid, uint64_t gid)
{
	uint64_t uid_idx;
	uint64_t gid_idx;
	int domcnt = 0;

	uid_idx = FUID_INDEX(uid);
	gid_idx = FUID_INDEX(gid);
	if (uid_idx)
		domcnt++;
	if (gid_idx > 0 && gid_idx != uid_idx)
		domcnt++;

	return (domcnt);
}