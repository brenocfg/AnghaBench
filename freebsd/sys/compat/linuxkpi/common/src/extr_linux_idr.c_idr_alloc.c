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
struct idr {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int idr_alloc_locked (struct idr*,void*,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
idr_alloc(struct idr *idr, void *ptr, int start, int end, gfp_t gfp_mask)
{
	int retval;

	mtx_lock(&idr->lock);
	retval = idr_alloc_locked(idr, ptr, start, end);
	mtx_unlock(&idr->lock);
	return (retval);
}