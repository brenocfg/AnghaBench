#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ocs_varray_t ;

/* Variables and functions */
 void* _ocs_varray_iter_next (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

void *
ocs_varray_iter_next(ocs_varray_t *va)
{
	void *rval = NULL;

	if (va != NULL) {
		ocs_lock(&va->lock);
			rval = _ocs_varray_iter_next(va);
		ocs_unlock(&va->lock);
	}
	return rval;
}