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
struct idr_layer {int bitmap; void** ary; } ;
struct idr {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IDR_MASK ; 
 struct idr_layer* idr_find_layer_locked (struct idr*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void *
idr_replace(struct idr *idr, void *ptr, int id)
{
	struct idr_layer *il;
	void *res;
	int idx;

	mtx_lock(&idr->lock);
	il = idr_find_layer_locked(idr, id);
	idx = id & IDR_MASK;

	/* Replace still returns an error if the item was not allocated. */
	if (il == NULL || (il->bitmap & (1 << idx))) {
		res = ERR_PTR(-ENOENT);
	} else {
		res = il->ary[idx];
		il->ary[idx] = ptr;
	}
	mtx_unlock(&idr->lock);
	return (res);
}