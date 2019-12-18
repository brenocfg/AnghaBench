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
struct vnode {struct fifoinfo* v_fifoinfo; } ;
struct fifoinfo {scalar_t__ fi_readers; scalar_t__ fi_writers; int /*<<< orphan*/  fi_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  M_VNODE ; 
 int /*<<< orphan*/  free (struct fifoinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_dtor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fifo_cleanup(struct vnode *vp)
{
	struct fifoinfo *fip;

	ASSERT_VOP_ELOCKED(vp, "fifo_cleanup");
	fip = vp->v_fifoinfo;
	if (fip->fi_readers == 0 && fip->fi_writers == 0) {
		vp->v_fifoinfo = NULL;
		pipe_dtor(fip->fi_pipe);
		free(fip, M_VNODE);
	}
}