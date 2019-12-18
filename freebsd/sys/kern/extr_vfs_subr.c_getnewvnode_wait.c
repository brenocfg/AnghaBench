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

/* Variables and functions */
 int ENFILE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PVFS ; 
 scalar_t__ desiredvnodes ; 
 int freevnodes ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ numvnodes ; 
 int /*<<< orphan*/  vnlru_free_locked (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnlruproc ; 
 int vnlruproc_sig ; 
 int /*<<< orphan*/  vnode_free_list_mtx ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getnewvnode_wait(int suspended)
{

	mtx_assert(&vnode_free_list_mtx, MA_OWNED);
	if (numvnodes >= desiredvnodes) {
		if (suspended) {
			/*
			 * The file system is being suspended.  We cannot
			 * risk a deadlock here, so allow allocation of
			 * another vnode even if this would give too many.
			 */
			return (0);
		}
		if (vnlruproc_sig == 0) {
			vnlruproc_sig = 1;	/* avoid unnecessary wakeups */
			wakeup(vnlruproc);
		}
		msleep(&vnlruproc_sig, &vnode_free_list_mtx, PVFS,
		    "vlruwk", hz);
	}
	/* Post-adjust like the pre-adjust in getnewvnode(). */
	if (numvnodes + 1 > desiredvnodes && freevnodes > 1)
		vnlru_free_locked(1, NULL);
	return (numvnodes >= desiredvnodes ? ENFILE : 0);
}