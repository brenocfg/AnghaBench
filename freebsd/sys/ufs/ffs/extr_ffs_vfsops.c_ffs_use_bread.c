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
struct buf {int b_flags; int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int B_INVAL ; 
 int B_NOCACHE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_UFSMNT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,int) ; 
 int bread (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  btodb (int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_use_bread(void *devfd, off_t loc, void **bufp, int size)
{
	struct buf *bp;
	int error;

	KASSERT(*bufp == NULL, ("ffs_use_bread: non-NULL *bufp %p\n", *bufp));
	*bufp = malloc(size, M_UFSMNT, M_WAITOK);
	if ((error = bread((struct vnode *)devfd, btodb(loc), size, NOCRED,
	    &bp)) != 0)
		return (error);
	bcopy(bp->b_data, *bufp, size);
	bp->b_flags |= B_INVAL | B_NOCACHE;
	brelse(bp);
	return (0);
}