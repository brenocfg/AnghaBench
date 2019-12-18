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
struct pfr_buffer {size_t pfrb_type; int pfrb_msize; int /*<<< orphan*/ * pfrb_caddr; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t PFRB_MAX ; 
 size_t SIZE_T_MAX ; 
 size_t* buf_esize ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

int
pfr_buf_grow(struct pfr_buffer *b, int minsize)
{
	caddr_t p;
	size_t bs;

	if (b == NULL || b->pfrb_type <= 0 || b->pfrb_type >= PFRB_MAX) {
		errno = EINVAL;
		return (-1);
	}
	if (minsize != 0 && minsize <= b->pfrb_msize)
		return (0);
	bs = buf_esize[b->pfrb_type];
	if (!b->pfrb_msize) {
		if (minsize < 64)
			minsize = 64;
		b->pfrb_caddr = calloc(bs, minsize);
		if (b->pfrb_caddr == NULL)
			return (-1);
		b->pfrb_msize = minsize;
	} else {
		if (minsize == 0)
			minsize = b->pfrb_msize * 2;
		if (minsize < 0 || minsize >= SIZE_T_MAX / bs) {
			/* msize overflow */
			errno = ENOMEM;
			return (-1);
		}
		p = realloc(b->pfrb_caddr, minsize * bs);
		if (p == NULL)
			return (-1);
		bzero(p + b->pfrb_msize * bs, (minsize - b->pfrb_msize) * bs);
		b->pfrb_caddr = p;
		b->pfrb_msize = minsize;
	}
	return (0);
}