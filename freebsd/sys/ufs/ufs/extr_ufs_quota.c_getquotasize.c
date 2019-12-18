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
typedef  int /*<<< orphan*/  u_long ;
struct ufsmount {scalar_t__* um_quotas; int* um_qflags; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NULLVP ; 
 int QTF_64BIT ; 
 int QTF_CLOSING ; 
 int /*<<< orphan*/  UFS_LOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UFS_UNLOCK (struct ufsmount*) ; 
 struct ufsmount* VFSTOUFS (struct mount*) ; 
 int copyout (int*,void*,int) ; 

int
getquotasize(struct thread *td, struct mount *mp, u_long id, int type,
    void *sizep)
{
	struct ufsmount *ump = VFSTOUFS(mp);
	int bitsize;

	UFS_LOCK(ump);
	if (ump->um_quotas[type] == NULLVP ||
	    (ump->um_qflags[type] & QTF_CLOSING)) {
		UFS_UNLOCK(ump);
		return (EINVAL);
	}
	if ((ump->um_qflags[type] & QTF_64BIT) != 0)
		bitsize = 64;
	else
		bitsize = 32;
	UFS_UNLOCK(ump);
	return (copyout(&bitsize, sizep, sizeof(int)));
}