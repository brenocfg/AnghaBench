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
struct idr_layer {int bitmap; struct idr_layer** ary; } ;
struct idr {int layers; struct idr_layer* top; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int IDR_BITS ; 
 int IDR_MASK ; 
 int IDR_SIZE ; 
 int MAX_LEVEL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int find_next_bit (int*,int,int) ; 
 void* idr_find_locked (struct idr*,int) ; 
 void* idr_get (struct idr*) ; 
 int idr_pos (int,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct idr*,...) ; 

__attribute__((used)) static int
idr_get_new_above_locked(struct idr *idr, void *ptr, int starting_id, int *idp)
{
	struct idr_layer *stack[MAX_LEVEL];
	struct idr_layer *il;
	int error;
	int layer;
	int idx, sidx;
	int id;

	mtx_assert(&idr->lock, MA_OWNED);

	error = -EAGAIN;
	/*
	 * Compute the layers required to support starting_id and the mask
	 * at the top layer.
	 */
restart:
	idx = starting_id;
	layer = 0;
	while (idx & ~IDR_MASK) {
		layer++;
		idx >>= IDR_BITS;
	}
	if (layer == MAX_LEVEL + 1) {
		error = -ENOSPC;
		goto out;
	}
	/*
	 * Expand the tree until there is free space at or beyond starting_id.
	 */
	while (idr->layers <= layer ||
	    idr->top->bitmap < (1 << idr_pos(starting_id, idr->layers - 1))) {
		if (idr->layers == MAX_LEVEL + 1) {
			error = -ENOSPC;
			goto out;
		}
		il = idr_get(idr);
		if (il == NULL)
			goto out;
		il->ary[0] = idr->top;
		if (idr->top && idr->top->bitmap == 0)
			il->bitmap &= ~1;
		idr->top = il;
		idr->layers++;
	}
	il = idr->top;
	id = 0;
	/*
	 * Walk the tree following free bitmaps, record our path.
	 */
	for (layer = idr->layers - 1;; layer--) {
		stack[layer] = il;
		sidx = idr_pos(starting_id, layer);
		/* Returns index numbered from 0 or size if none exists. */
		idx = find_next_bit(&il->bitmap, IDR_SIZE, sidx);
		if (idx == IDR_SIZE && sidx == 0)
			panic("idr_get_new: Invalid leaf state (%p, %p)\n",
			    idr, il);
		/*
		 * We may have walked a path where there was a free bit but
		 * it was lower than what we wanted.  Restart the search with
		 * a larger starting id.  id contains the progress we made so
		 * far.  Search the leaf one above this level.  This may
		 * restart as many as MAX_LEVEL times but that is expected
		 * to be rare.
		 */
		if (idx == IDR_SIZE) {
			starting_id = id + (1 << ((layer + 1) * IDR_BITS));
			goto restart;
		}
		if (idx > sidx)
			starting_id = 0;	/* Search the whole subtree. */
		id |= idx << (layer * IDR_BITS);
		if (layer == 0)
			break;
		if (il->ary[idx] == NULL) {
			il->ary[idx] = idr_get(idr);
			if (il->ary[idx] == NULL)
				goto out;
		}
		il = il->ary[idx];
	}
	/*
	 * Allocate the leaf to the consumer.
	 */
	il->bitmap &= ~(1 << idx);
	il->ary[idx] = ptr;
	*idp = id;
	/*
	 * Clear bitmaps potentially up to the root.
	 */
	while (il->bitmap == 0 && ++layer < idr->layers) {
		il = stack[layer];
		il->bitmap &= ~(1 << idr_pos(id, layer));
	}
	error = 0;
out:
#ifdef INVARIANTS
	if (error == 0 && idr_find_locked(idr, id) != ptr) {
		panic("idr_get_new_above: Failed for idr %p, id %d, ptr %p\n",
		    idr, id, ptr);
	}
#endif
	return (error);
}