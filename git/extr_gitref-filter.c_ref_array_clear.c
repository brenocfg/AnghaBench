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
struct ref_array {int nr; int alloc; TYPE_1__* items; } ;
struct TYPE_4__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_array_item (TYPE_1__) ; 
 TYPE_1__* used_atom ; 
 int used_atom_cnt ; 

void ref_array_clear(struct ref_array *array)
{
	int i;

	for (i = 0; i < used_atom_cnt; i++)
		free((char *)used_atom[i].name);
	FREE_AND_NULL(used_atom);
	used_atom_cnt = 0;
	for (i = 0; i < array->nr; i++)
		free_array_item(array->items[i]);
	FREE_AND_NULL(array->items);
	array->nr = array->alloc = 0;
}