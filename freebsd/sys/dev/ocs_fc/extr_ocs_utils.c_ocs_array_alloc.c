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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
struct TYPE_4__ {int size; int count; int elems_per_row; int n_rows; int bytes_per_row; int array_rows_len; int /*<<< orphan*/ ** array_rows; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_array_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_array_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 void* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 int slab_len ; 

ocs_array_t *
ocs_array_alloc(ocs_os_handle_t os, uint32_t size, uint32_t count)
{
	ocs_array_t *array = NULL;
	uint32_t i;

	/* Fail if the item size exceeds slab_len - caller should increase slab_size,
	 * or not use this API.
	 */
	if (size > slab_len) {
		ocs_log_err(NULL, "Error: size exceeds slab length\n");
		return NULL;
	}

	array = ocs_malloc(os, sizeof(*array), OCS_M_ZERO | OCS_M_NOWAIT);
	if (array == NULL) {
		return NULL;
	}

	array->os = os;
	array->size = size;
	array->count = count;
	array->elems_per_row = slab_len / size;
	array->n_rows = (count + array->elems_per_row - 1) / array->elems_per_row;
	array->bytes_per_row = array->elems_per_row * array->size;

	array->array_rows_len = array->n_rows * sizeof(*array->array_rows);
	array->array_rows = ocs_malloc(os, array->array_rows_len, OCS_M_ZERO | OCS_M_NOWAIT);
	if (array->array_rows == NULL) {
		ocs_array_free(array);
		return NULL;
	}
	for (i = 0; i < array->n_rows; i++) {
		array->array_rows[i] = ocs_malloc(os, array->bytes_per_row, OCS_M_ZERO | OCS_M_NOWAIT);
		if (array->array_rows[i] == NULL) {
			ocs_array_free(array);
			return NULL;
		}
	}

	return array;
}