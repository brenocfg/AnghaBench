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
struct dba_array {size_t ea; size_t eu; int flags; scalar_t__* em; void** ep; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 int DBA_STR ; 
 int /*<<< orphan*/  assert (int) ; 
 void* mandoc_strdup (void*) ; 

void
dba_array_set(struct dba_array *array, int32_t ie, void *entry)
{
	assert(ie >= 0);
	assert(ie < array->ea);
	assert(ie <= array->eu);
	if (ie == array->eu)
		array->eu++;
	if (array->flags & DBA_STR)
		entry = mandoc_strdup(entry);
	array->ep[ie] = entry;
	array->em[ie] = 0;
}