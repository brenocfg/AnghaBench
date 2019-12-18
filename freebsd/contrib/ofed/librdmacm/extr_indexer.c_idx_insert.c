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
union idx_entry {int next; void* item; } ;
struct indexer {int free_list; union idx_entry** array; } ;

/* Variables and functions */
 size_t idx_array_index (int) ; 
 size_t idx_entry_index (int) ; 
 int idx_grow (struct indexer*) ; 

int idx_insert(struct indexer *idx, void *item)
{
	union idx_entry *entry;
	int index;

	if ((index = idx->free_list) == 0) {
		if ((index = idx_grow(idx)) <= 0)
			return index;
	}

	entry = idx->array[idx_array_index(index)];
	idx->free_list = entry[idx_entry_index(index)].next;
	entry[idx_entry_index(index)].item = item;
	return index;
}