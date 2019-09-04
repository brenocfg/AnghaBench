#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_id {int* hash; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; struct object_entry* next; } ;

/* Variables and functions */
 struct object_entry* new_object (struct object_id*) ; 
 struct object_entry** object_table ; 
 scalar_t__ oideq (struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct object_entry *insert_object(struct object_id *oid)
{
	unsigned int h = oid->hash[0] << 8 | oid->hash[1];
	struct object_entry *e = object_table[h];

	while (e) {
		if (oideq(oid, &e->idx.oid))
			return e;
		e = e->next;
	}

	e = new_object(oid);
	e->next = object_table[h];
	e->idx.offset = 0;
	object_table[h] = e;
	return e;
}