#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mount {int mnt_kern_flag; int /*<<< orphan*/  mnt_writeopcount; int /*<<< orphan*/  mnt_flag; TYPE_1__* mnt_vfc; TYPE_2__* mnt_susp_owner; } ;
struct TYPE_4__ {int td_pflags; } ;
struct TYPE_3__ {int vfc_flags; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MNTK_SUSPEND ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int PCATCH ; 
 int PUSER ; 
 int TDP_IGNSUSP ; 
 int VFCF_SBDRY ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 scalar_t__ __predict_true (int) ; 
 TYPE_2__* curthread ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_mp_count_add_pcpu (struct mount*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vfs_op_thread_enter (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_thread_exit (struct mount*) ; 
 int /*<<< orphan*/  writeopcount ; 

__attribute__((used)) static int
vn_start_write_refed(struct mount *mp, int flags, bool mplocked)
{
	int error, mflags;

	if (__predict_true(!mplocked) && (flags & V_XSLEEP) == 0 &&
	    vfs_op_thread_enter(mp)) {
		MPASS((mp->mnt_kern_flag & MNTK_SUSPEND) == 0);
		vfs_mp_count_add_pcpu(mp, writeopcount, 1);
		vfs_op_thread_exit(mp);
		return (0);
	}

	if (mplocked)
		mtx_assert(MNT_MTX(mp), MA_OWNED);
	else
		MNT_ILOCK(mp);

	error = 0;

	/*
	 * Check on status of suspension.
	 */
	if ((curthread->td_pflags & TDP_IGNSUSP) == 0 ||
	    mp->mnt_susp_owner != curthread) {
		mflags = ((mp->mnt_vfc->vfc_flags & VFCF_SBDRY) != 0 ?
		    (flags & PCATCH) : 0) | (PUSER - 1);
		while ((mp->mnt_kern_flag & MNTK_SUSPEND) != 0) {
			if (flags & V_NOWAIT) {
				error = EWOULDBLOCK;
				goto unlock;
			}
			error = msleep(&mp->mnt_flag, MNT_MTX(mp), mflags,
			    "suspfs", 0);
			if (error)
				goto unlock;
		}
	}
	if (flags & V_XSLEEP)
		goto unlock;
	mp->mnt_writeopcount++;
unlock:
	if (error != 0 || (flags & V_XSLEEP) != 0)
		MNT_REL(mp);
	MNT_IUNLOCK(mp);
	return (error);
}