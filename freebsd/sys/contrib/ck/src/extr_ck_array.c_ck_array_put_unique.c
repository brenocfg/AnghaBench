#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ck_array {unsigned int n_entries; TYPE_2__* active; TYPE_1__* transaction; } ;
struct TYPE_4__ {void** values; } ;
struct TYPE_3__ {void** values; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_array_put (struct ck_array*,void*) ; 

int
ck_array_put_unique(struct ck_array *array, void *value)
{
	unsigned int i, limit;
	void **v;

	limit = array->n_entries;
	if (array->transaction != NULL) {
		v = array->transaction->values;
	} else {
		v = array->active->values;
	}

	for (i = 0; i < limit; i++) {
		if (v[i] == value)
			return 1;
	}

	return -!ck_array_put(array, value);
}