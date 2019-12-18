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
struct oid_array {int nr; scalar_t__ oid; } ;
typedef  int (* for_each_oid_fn ) (scalar_t__,void*) ;

/* Variables and functions */

int oid_array_for_each(struct oid_array *array,
		       for_each_oid_fn fn,
		       void *data)
{
	int i;

	/* No oid_array_sort() here! See the api-oid-array.txt docs! */

	for (i = 0; i < array->nr; i++) {
		int ret = fn(array->oid + i, data);
		if (ret)
			return ret;
	}
	return 0;
}