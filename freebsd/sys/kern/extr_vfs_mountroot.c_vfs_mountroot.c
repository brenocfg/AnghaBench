#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct thread {int dummy; } ;
struct sbuf {int dummy; } ;
struct mount {scalar_t__ mnt_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  pr_mtx; int /*<<< orphan*/  pr_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 struct mount* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mount* TAILQ_NEXT (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  inittodr (scalar_t__) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mountroot ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ prison0 ; 
 int /*<<< orphan*/  root_holds_mtx ; 
 int /*<<< orphan*/  root_mount_complete ; 
 int /*<<< orphan*/  rootvnode ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  vfs_mountroot_conf0 (struct sbuf*) ; 
 int vfs_mountroot_devfs (struct thread*,struct mount**) ; 
 int vfs_mountroot_parse (struct sbuf*,struct mount*) ; 
 int vfs_mountroot_readconf (struct thread*,struct sbuf*) ; 
 int /*<<< orphan*/  vfs_mountroot_shuffle (struct thread*,struct mount*) ; 
 int /*<<< orphan*/  vref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
vfs_mountroot(void)
{
	struct mount *mp;
	struct sbuf *sb;
	struct thread *td;
	time_t timebase;
	int error;
	
	mtx_assert(&Giant, MA_NOTOWNED);

	TSENTER();

	td = curthread;

	sb = sbuf_new_auto();
	vfs_mountroot_conf0(sb);
	sbuf_finish(sb);

	error = vfs_mountroot_devfs(td, &mp);
	while (!error) {
		error = vfs_mountroot_parse(sb, mp);
		if (!error) {
			vfs_mountroot_shuffle(td, mp);
			sbuf_clear(sb);
			error = vfs_mountroot_readconf(td, sb);
			sbuf_finish(sb);
		}
	}

	sbuf_delete(sb);

	/*
	 * Iterate over all currently mounted file systems and use
	 * the time stamp found to check and/or initialize the RTC.
	 * Call inittodr() only once and pass it the largest of the
	 * timestamps we encounter.
	 */
	timebase = 0;
	mtx_lock(&mountlist_mtx);
	mp = TAILQ_FIRST(&mountlist);
	while (mp != NULL) {
		if (mp->mnt_time > timebase)
			timebase = mp->mnt_time;
		mp = TAILQ_NEXT(mp, mnt_list);
	}
	mtx_unlock(&mountlist_mtx);
	inittodr(timebase);

	/* Keep prison0's root in sync with the global rootvnode. */
	mtx_lock(&prison0.pr_mtx);
	prison0.pr_root = rootvnode;
	vref(prison0.pr_root);
	mtx_unlock(&prison0.pr_mtx);

	mtx_lock(&root_holds_mtx);
	atomic_store_rel_int(&root_mount_complete, 1);
	wakeup(&root_mount_complete);
	mtx_unlock(&root_holds_mtx);

	EVENTHANDLER_INVOKE(mountroot);

	TSEXIT();
}