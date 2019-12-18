#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ entry_count; scalar_t__ array_count; int /*<<< orphan*/  lock; void** array; } ;
typedef  TYPE_1__ ocs_varray_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
ocs_varray_add(ocs_varray_t *va, void *entry)
{
	uint32_t rc = -1;

	ocs_lock(&va->lock);
		if (va->entry_count < va->array_count) {
			va->array[va->entry_count++] = entry;
			rc = 0;
		}
	ocs_unlock(&va->lock);

	return rc;
}