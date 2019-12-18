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
struct idr {int next_cyclic_id; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOSPC ; 
 int idr_alloc_locked (struct idr*,void*,int,int) ; 
 scalar_t__ likely (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int
idr_alloc_cyclic(struct idr *idr, void *ptr, int start, int end, gfp_t gfp_mask)
{
	int retval;

	mtx_lock(&idr->lock);
	retval = idr_alloc_locked(idr, ptr, max(start, idr->next_cyclic_id), end);
	if (unlikely(retval == -ENOSPC))
		retval = idr_alloc_locked(idr, ptr, start, end);
	if (likely(retval >= 0))
		idr->next_cyclic_id = retval + 1;
	mtx_unlock(&idr->lock);
	return (retval);
}