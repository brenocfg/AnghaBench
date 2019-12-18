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
struct buf {int b_flags; int b_bufsize; scalar_t__ b_blkno; scalar_t__ b_lblkno; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 scalar_t__ BUF_LOCK (struct buf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int B_CLUSTEROK ; 
 int B_DELWRI ; 
 int B_INVAL ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 struct buf* gbincore (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
vfs_bio_clcheck(struct vnode *vp, int size, daddr_t lblkno, daddr_t blkno)
{
	struct buf *bpa;
	int match;

	match = 0;

	/* If the buf isn't in core skip it */
	if ((bpa = gbincore(&vp->v_bufobj, lblkno)) == NULL)
		return (0);

	/* If the buf is busy we don't want to wait for it */
	if (BUF_LOCK(bpa, LK_EXCLUSIVE | LK_NOWAIT, NULL) != 0)
		return (0);

	/* Only cluster with valid clusterable delayed write buffers */
	if ((bpa->b_flags & (B_DELWRI | B_CLUSTEROK | B_INVAL)) !=
	    (B_DELWRI | B_CLUSTEROK))
		goto done;

	if (bpa->b_bufsize != size)
		goto done;

	/*
	 * Check to see if it is in the expected place on disk and that the
	 * block has been mapped.
	 */
	if ((bpa->b_blkno != bpa->b_lblkno) && (bpa->b_blkno == blkno))
		match = 1;
done:
	BUF_UNLOCK(bpa);
	return (match);
}