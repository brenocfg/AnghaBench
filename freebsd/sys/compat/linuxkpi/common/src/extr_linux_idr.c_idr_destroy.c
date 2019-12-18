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
struct idr {int /*<<< orphan*/  lock; struct idr_layer* free; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IDR ; 
 int /*<<< orphan*/  free (struct idr_layer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove_all (struct idr*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
idr_destroy(struct idr *idr)
{
	struct idr_layer *il, *iln;

	idr_remove_all(idr);
	mtx_lock(&idr->lock);
	for (il = idr->free; il != NULL; il = iln) {
		iln = il->ary[0];
		free(il, M_IDR);
	}
	mtx_unlock(&idr->lock);
	mtx_destroy(&idr->lock);
}