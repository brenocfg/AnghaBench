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
struct vnode {int dummy; } ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int getblkx (struct vnode*,int /*<<< orphan*/ ,int,int,int,int,struct buf**) ; 

struct buf *
getblk(struct vnode *vp, daddr_t blkno, int size, int slpflag, int slptimeo,
    int flags)
{
	struct buf *bp;
	int error;

	error = getblkx(vp, blkno, size, slpflag, slptimeo, flags, &bp);
	if (error != 0)
		return (NULL);
	return (bp);
}