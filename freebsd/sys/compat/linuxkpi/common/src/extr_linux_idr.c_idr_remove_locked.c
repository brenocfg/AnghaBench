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
struct idr {int layers; struct idr_layer* top; } ;

/* Variables and functions */
 int IDR_MASK ; 
 int MAX_ID_MASK ; 
 int idr_max (struct idr*) ; 
 int idr_pos (int,int) ; 
 int /*<<< orphan*/  panic (char*,int,struct idr*,struct idr_layer*) ; 

__attribute__((used)) static void *
idr_remove_locked(struct idr *idr, int id)
{
	struct idr_layer *il;
	void *res;
	int layer;
	int idx;

	id &= MAX_ID_MASK;
	il = idr->top;
	layer = idr->layers - 1;
	if (il == NULL || id > idr_max(idr))
		return (NULL);
	/*
	 * Walk down the tree to this item setting bitmaps along the way
	 * as we know at least one item will be free along this path.
	 */
	while (layer && il) {
		idx = idr_pos(id, layer);
		il->bitmap |= 1 << idx;
		il = il->ary[idx];
		layer--;
	}
	idx = id & IDR_MASK;
	/*
	 * At this point we've set free space bitmaps up the whole tree.
	 * We could make this non-fatal and unwind but linux dumps a stack
	 * and a warning so I don't think it's necessary.
	 */
	if (il == NULL || (il->bitmap & (1 << idx)) != 0)
		panic("idr_remove: Item %d not allocated (%p, %p)\n",
		    id, idr, il);
	res = il->ary[idx];
	il->ary[idx] = NULL;
	il->bitmap |= 1 << idx;

	return (res);
}