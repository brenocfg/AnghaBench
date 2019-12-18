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
struct ck_array {unsigned int n_entries; struct _ck_array* transaction; struct _ck_array* active; int /*<<< orphan*/  allocator; } ;
struct _ck_array {void** values; unsigned int n_committed; int length; } ;

/* Variables and functions */
 struct _ck_array* ck_array_create (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (void**,void*) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 

bool
ck_array_remove(struct ck_array *array, void *value)
{
	struct _ck_array *target;
	unsigned int i;

	if (array->transaction != NULL) {
		target = array->transaction;

		for (i = 0; i < array->n_entries; i++) {
			if (target->values[i] == value) {
				target->values[i] = target->values[--array->n_entries];
				return true;
			}
		}

		return false;
	}

	target = array->active;

	for (i = 0; i < array->n_entries; i++) {
		if (target->values[i] == value)
			break;
	}

	if (i == array->n_entries)
		return false;

	/* If there are pending additions, immediately eliminate the operation. */
	if (target->n_committed != array->n_entries) {
		ck_pr_store_ptr(&target->values[i], target->values[--array->n_entries]);
		return true;
	}

	/*
	 * The assumption is that these allocations are small to begin with.
	 * If there is no immediate opportunity for transaction, allocate a
	 * transactional array which will be applied upon commit time.
	 */
	target = ck_array_create(array->allocator, array->n_entries);
	if (target == NULL)
		return false;

	memcpy(target->values, array->active->values, sizeof(void *) * array->n_entries);
	target->length = array->n_entries;
	target->n_committed = array->n_entries;
	target->values[i] = target->values[--array->n_entries];

	array->transaction = target;
	return true;
}