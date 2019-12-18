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
struct TYPE_3__ {size_t next_index; size_t entry_count; void** array; } ;
typedef  TYPE_1__ ocs_varray_t ;

/* Variables and functions */

void *
_ocs_varray_iter_next(ocs_varray_t *va)
{
	void *rval;

	rval = va->array[va->next_index];
	if (++va->next_index >= va->entry_count) {
		va->next_index = 0;
	}
	return rval;
}