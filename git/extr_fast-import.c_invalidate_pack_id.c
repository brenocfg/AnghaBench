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
struct tag {unsigned int pack_id; struct tag* next_tag; } ;
struct object_entry {unsigned int pack_id; struct object_entry* next; } ;
struct branch {unsigned int pack_id; struct branch* table_next_branch; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct object_entry**) ; 
 void* MAX_PACK_ID ; 
 struct branch** branch_table ; 
 unsigned long branch_table_sz ; 
 struct tag* first_tag ; 
 struct object_entry** object_table ; 

__attribute__((used)) static void invalidate_pack_id(unsigned int id)
{
	unsigned int h;
	unsigned long lu;
	struct tag *t;

	for (h = 0; h < ARRAY_SIZE(object_table); h++) {
		struct object_entry *e;

		for (e = object_table[h]; e; e = e->next)
			if (e->pack_id == id)
				e->pack_id = MAX_PACK_ID;
	}

	for (lu = 0; lu < branch_table_sz; lu++) {
		struct branch *b;

		for (b = branch_table[lu]; b; b = b->table_next_branch)
			if (b->pack_id == id)
				b->pack_id = MAX_PACK_ID;
	}

	for (t = first_tag; t; t = t->next_tag)
		if (t->pack_id == id)
			t->pack_id = MAX_PACK_ID;
}