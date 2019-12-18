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
struct cdeque {int size; int cap_mask; size_t* arr; size_t end_pos; } ;

/* Variables and functions */
 int CDE_OK ; 
 int CDE_OUT_OF_BOUNDS ; 
 int CDE_PARAM ; 

__attribute__((used)) static int cdeque_push_back(struct cdeque* d, void* item) {
	if(d == NULL)
		return CDE_PARAM;

	if(d->size == d->cap_mask + 1)
		return CDE_OUT_OF_BOUNDS;

	d->arr[d->end_pos] = (size_t) item;
	d->end_pos = (d->end_pos + 1) & d->cap_mask;
	d->size++;

	return CDE_OK;
}