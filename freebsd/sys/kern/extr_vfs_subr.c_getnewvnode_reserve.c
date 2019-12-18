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
typedef  scalar_t__ u_int ;
struct thread {scalar_t__ td_vp_reserv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_long (scalar_t__*,int) ; 
 scalar_t__ atomic_fetchadd_long (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  atomic_subtract_long (scalar_t__*,scalar_t__) ; 
 struct thread* curthread ; 
 scalar_t__ desiredvnodes ; 
 scalar_t__ freevnodes ; 
 scalar_t__ getnewvnode_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ numvnodes ; 
 int /*<<< orphan*/  ulmin (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vcheckspace () ; 
 int /*<<< orphan*/  vnlru_free_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_free_list_mtx ; 
 scalar_t__ wantfreevnodes ; 

void
getnewvnode_reserve(u_int count)
{
	struct thread *td;

	/* Pre-adjust like the pre-adjust in getnewvnode(), with any count. */
	/* XXX no longer so quick, but this part is not racy. */
	mtx_lock(&vnode_free_list_mtx);
	if (numvnodes + count > desiredvnodes && freevnodes > wantfreevnodes)
		vnlru_free_locked(ulmin(numvnodes + count - desiredvnodes,
		    freevnodes - wantfreevnodes), NULL);
	mtx_unlock(&vnode_free_list_mtx);

	td = curthread;
	/* First try to be quick and racy. */
	if (atomic_fetchadd_long(&numvnodes, count) + count <= desiredvnodes) {
		td->td_vp_reserv += count;
		vcheckspace();	/* XXX no longer so quick, but more racy */
		return;
	} else
		atomic_subtract_long(&numvnodes, count);

	mtx_lock(&vnode_free_list_mtx);
	while (count > 0) {
		if (getnewvnode_wait(0) == 0) {
			count--;
			td->td_vp_reserv++;
			atomic_add_long(&numvnodes, 1);
		}
	}
	vcheckspace();
	mtx_unlock(&vnode_free_list_mtx);
}