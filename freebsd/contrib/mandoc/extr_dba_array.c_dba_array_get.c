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
struct dba_array {size_t eu; int* em; void** ep; } ;
typedef  size_t int32_t ;

/* Variables and functions */

void *
dba_array_get(struct dba_array *array, int32_t ie)
{
	if (ie < 0 || ie >= array->eu || array->em[ie] == -1)
		return NULL;
	return array->ep[ie];
}