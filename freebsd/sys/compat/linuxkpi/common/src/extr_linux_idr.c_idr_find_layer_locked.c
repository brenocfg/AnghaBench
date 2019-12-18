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
struct idr_layer {struct idr_layer** ary; } ;
struct idr {int layers; struct idr_layer* top; } ;

/* Variables and functions */
 int MAX_ID_MASK ; 
 int idr_max (struct idr*) ; 
 size_t idr_pos (int,int) ; 

__attribute__((used)) static inline struct idr_layer *
idr_find_layer_locked(struct idr *idr, int id)
{
	struct idr_layer *il;
	int layer;

	id &= MAX_ID_MASK;
	il = idr->top;
	layer = idr->layers - 1;
	if (il == NULL || id > idr_max(idr))
		return (NULL);
	while (layer && il) {
		il = il->ary[idr_pos(id, layer)];
		layer--;
	}
	return (il);
}