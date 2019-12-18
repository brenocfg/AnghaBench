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
struct idr_layer {void** ary; } ;
struct idr {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int IDR_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct idr_layer* idr_find_layer_locked (struct idr*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *
idr_find_locked(struct idr *idr, int id)
{
	struct idr_layer *il;
	void *res;

	mtx_assert(&idr->lock, MA_OWNED);
	il = idr_find_layer_locked(idr, id);
	if (il != NULL)
		res = il->ary[id & IDR_MASK];
	else
		res = NULL;
	return (res);
}