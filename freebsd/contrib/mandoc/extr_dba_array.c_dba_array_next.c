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
struct dba_array {size_t ec; size_t eu; int* em; void** ep; } ;

/* Variables and functions */

void *
dba_array_next(struct dba_array *array)
{
	if (array->ec < array->eu)
		array->ec++;
	else
		array->ec = 0;
	while (array->ec < array->eu && array->em[array->ec] == -1)
		array->ec++;
	return array->ec < array->eu ? array->ep[array->ec] : NULL;
}