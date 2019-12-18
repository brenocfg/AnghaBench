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
struct buf {int b_kvasize; } ;

/* Variables and functions */
 int BKVAMASK ; 
 int ENOSPC ; 
 int GB_KVAALLOC ; 
 int GB_UNMAPPED ; 
 scalar_t__ bufkva_alloc (struct buf*,int,int) ; 

__attribute__((used)) static int
getnewbuf_kva(struct buf *bp, int gbflags, int maxsize)
{

	if ((gbflags & (GB_UNMAPPED | GB_KVAALLOC)) != GB_UNMAPPED) {
		/*
		 * In order to keep fragmentation sane we only allocate kva
		 * in BKVASIZE chunks.  XXX with vmem we can do page size.
		 */
		maxsize = (maxsize + BKVAMASK) & ~BKVAMASK;

		if (maxsize != bp->b_kvasize &&
		    bufkva_alloc(bp, maxsize, gbflags))
			return (ENOSPC);
	}
	return (0);
}