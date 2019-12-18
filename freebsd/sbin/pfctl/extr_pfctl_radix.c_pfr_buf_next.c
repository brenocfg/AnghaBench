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
struct pfr_buffer {size_t pfrb_type; int pfrb_size; void* pfrb_caddr; } ;
typedef  size_t caddr_t ;

/* Variables and functions */
 size_t PFRB_MAX ; 
 size_t* buf_esize ; 

void *
pfr_buf_next(struct pfr_buffer *b, const void *prev)
{
	size_t bs;

	if (b == NULL || b->pfrb_type <= 0 || b->pfrb_type >= PFRB_MAX)
		return (NULL);
	if (b->pfrb_size == 0)
		return (NULL);
	if (prev == NULL)
		return (b->pfrb_caddr);
	bs = buf_esize[b->pfrb_type];
	if ((((caddr_t)prev)-((caddr_t)b->pfrb_caddr)) / bs >= b->pfrb_size-1)
		return (NULL);
	return (((caddr_t)prev) + bs);
}