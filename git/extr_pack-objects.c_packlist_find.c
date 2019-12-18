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
typedef  size_t uint32_t ;
struct packing_data {int* index; struct object_entry* objects; int /*<<< orphan*/  index_size; } ;
struct object_id {int dummy; } ;
struct object_entry {int dummy; } ;

/* Variables and functions */
 size_t locate_object_entry_hash (struct packing_data*,struct object_id const*,int*) ; 

struct object_entry *packlist_find(struct packing_data *pdata,
				   const struct object_id *oid)
{
	uint32_t i;
	int found;

	if (!pdata->index_size)
		return NULL;

	i = locate_object_entry_hash(pdata, oid, &found);

	if (!found)
		return NULL;

	return &pdata->objects[pdata->index[i] - 1];
}