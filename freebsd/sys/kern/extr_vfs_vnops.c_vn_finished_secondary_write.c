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
struct mount {scalar_t__ mnt_secondary_writes; int mnt_kern_flag; } ;

/* Variables and functions */
 int MNTK_SUSPEND ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
vn_finished_secondary_write(struct mount *mp)
{
	if (mp == NULL || !vn_suspendable(mp))
		return;
	MNT_ILOCK(mp);
	MNT_REL(mp);
	mp->mnt_secondary_writes--;
	if (mp->mnt_secondary_writes < 0)
		panic("vn_finished_secondary_write: neg cnt");
	if ((mp->mnt_kern_flag & MNTK_SUSPEND) != 0 &&
	    mp->mnt_secondary_writes <= 0)
		wakeup(&mp->mnt_secondary_writes);
	MNT_IUNLOCK(mp);
}