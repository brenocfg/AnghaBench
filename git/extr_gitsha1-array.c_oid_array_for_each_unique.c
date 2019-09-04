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
struct oid_array {int nr; scalar_t__ oid; int /*<<< orphan*/  sorted; } ;
typedef  int (* for_each_oid_fn ) (scalar_t__,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  oid_array_sort (struct oid_array*) ; 
 scalar_t__ oideq (scalar_t__,scalar_t__) ; 

int oid_array_for_each_unique(struct oid_array *array,
			      for_each_oid_fn fn,
			      void *data)
{
	int i;

	if (!array->sorted)
		oid_array_sort(array);

	for (i = 0; i < array->nr; i++) {
		int ret;
		if (i > 0 && oideq(array->oid + i, array->oid + i - 1))
			continue;
		ret = fn(array->oid + i, data);
		if (ret)
			return ret;
	}
	return 0;
}