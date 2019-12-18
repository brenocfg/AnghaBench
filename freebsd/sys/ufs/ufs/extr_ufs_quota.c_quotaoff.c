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
struct ufsmount {int* um_qflags; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int /*<<< orphan*/  PRIV_UFS_QUOTAOFF ; 
 int QTF_CLOSING ; 
 int QTF_OPENING ; 
 int /*<<< orphan*/  UFS_LOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UFS_UNLOCK (struct ufsmount*) ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int quotaoff_inchange (struct thread*,struct mount*,int) ; 

int
quotaoff(struct thread *td, struct mount *mp, int type)
{
	struct ufsmount *ump;
	int error;

	error = priv_check(td, PRIV_UFS_QUOTAOFF);
	if (error)
		return (error);

	ump = VFSTOUFS(mp);
	UFS_LOCK(ump);
	if ((ump->um_qflags[type] & (QTF_OPENING|QTF_CLOSING)) != 0) {
		UFS_UNLOCK(ump);
		return (EALREADY);
	}
	ump->um_qflags[type] |= QTF_CLOSING;
	UFS_UNLOCK(ump);

	return (quotaoff_inchange(td, mp, type));
}