#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  m; } ;
struct linux_idr_cache {int /*<<< orphan*/  count; struct idr_layer* head; TYPE_1__ lock; } ;
struct idr_layer {struct idr_layer** ary; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct idr_layer *
idr_preload_dequeue_locked(struct linux_idr_cache *lic)
{
	struct idr_layer *retval;

	/* check if wrong thread is trying to dequeue */
	if (mtx_owned(&lic->lock.m) == 0)
		return (NULL);

	retval = lic->head;
	if (likely(retval != NULL)) {
		lic->head = retval->ary[0];
		lic->count--;
		retval->ary[0] = NULL;
	}
	return (retval);
}