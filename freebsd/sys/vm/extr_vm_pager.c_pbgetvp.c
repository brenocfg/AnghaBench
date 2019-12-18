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
struct vnode {int /*<<< orphan*/  v_bufobj; } ;
struct buf {int /*<<< orphan*/ * b_bufobj; int /*<<< orphan*/  b_flags; struct vnode* b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_PAGING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

void
pbgetvp(struct vnode *vp, struct buf *bp)
{

	KASSERT(bp->b_vp == NULL, ("pbgetvp: not free"));
	KASSERT(bp->b_bufobj == NULL, ("pbgetvp: not free (bufobj)"));

	bp->b_vp = vp;
	bp->b_flags |= B_PAGING;
	bp->b_bufobj = &vp->v_bufobj;
}