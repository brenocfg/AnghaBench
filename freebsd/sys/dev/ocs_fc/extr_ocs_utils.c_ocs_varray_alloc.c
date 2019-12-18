#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int array_count; int /*<<< orphan*/  lock; scalar_t__ next_index; int /*<<< orphan*/ * array; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_varray_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 void* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 

ocs_varray_t *
ocs_varray_alloc(ocs_os_handle_t os, uint32_t array_count)
{
	ocs_varray_t *va;

	va = ocs_malloc(os, sizeof(*va), OCS_M_ZERO | OCS_M_NOWAIT);
	if (va != NULL) {
		va->os = os;
		va->array_count = array_count;
		va->array = ocs_malloc(os, sizeof(*va->array) * va->array_count, OCS_M_ZERO | OCS_M_NOWAIT);
		if (va->array != NULL) {
			va->next_index = 0;
			ocs_lock_init(os, &va->lock, "varray:%p", va);
		} else {
			ocs_free(os, va, sizeof(*va));
			va = NULL;
		}
	}
	return va;
}