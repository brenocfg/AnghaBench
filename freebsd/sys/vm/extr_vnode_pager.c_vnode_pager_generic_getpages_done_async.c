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
struct buf {int b_pgbefore; int b_npages; int b_pgafter; int /*<<< orphan*/ * b_vp; int /*<<< orphan*/ ** b_pages; int /*<<< orphan*/  b_caller1; int /*<<< orphan*/  (* b_pgiodone ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pbrelbo (struct buf*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 int vnode_pager_generic_getpages_done (struct buf*) ; 
 int /*<<< orphan*/  vnode_pbuf_zone ; 

__attribute__((used)) static void
vnode_pager_generic_getpages_done_async(struct buf *bp)
{
	int error;

	error = vnode_pager_generic_getpages_done(bp);
	/* Run the iodone upon the requested range. */
	bp->b_pgiodone(bp->b_caller1, bp->b_pages + bp->b_pgbefore,
	    bp->b_npages - bp->b_pgbefore - bp->b_pgafter, error);
	for (int i = 0; i < bp->b_npages; i++)
		bp->b_pages[i] = NULL;
	bp->b_vp = NULL;
	pbrelbo(bp);
	uma_zfree(vnode_pbuf_zone, bp);
}