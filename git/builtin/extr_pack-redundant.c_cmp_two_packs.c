#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pack_list {void* unique_objects; TYPE_1__* pack; int /*<<< orphan*/  remaining_objects; } ;
struct object_id {int dummy; } ;
struct llist_item {int dummy; } ;
struct TYPE_4__ {unsigned int rawsz; } ;
struct TYPE_3__ {unsigned char* index_data; int index_version; unsigned long num_objects; } ;

/* Variables and functions */
 int hashcmp (unsigned char const*,unsigned char const*) ; 
 void* llist_copy (int /*<<< orphan*/ ) ; 
 struct llist_item* llist_sorted_remove (void*,struct object_id const*,struct llist_item*) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static void cmp_two_packs(struct pack_list *p1, struct pack_list *p2)
{
	unsigned long p1_off = 0, p2_off = 0, p1_step, p2_step;
	const unsigned char *p1_base, *p2_base;
	struct llist_item *p1_hint = NULL, *p2_hint = NULL;
	const unsigned int hashsz = the_hash_algo->rawsz;

	if (!p1->unique_objects)
		p1->unique_objects = llist_copy(p1->remaining_objects);
	if (!p2->unique_objects)
		p2->unique_objects = llist_copy(p2->remaining_objects);

	p1_base = p1->pack->index_data;
	p2_base = p2->pack->index_data;
	p1_base += 256 * 4 + ((p1->pack->index_version < 2) ? 4 : 8);
	p2_base += 256 * 4 + ((p2->pack->index_version < 2) ? 4 : 8);
	p1_step = hashsz + ((p1->pack->index_version < 2) ? 4 : 0);
	p2_step = hashsz + ((p2->pack->index_version < 2) ? 4 : 0);

	while (p1_off < p1->pack->num_objects * p1_step &&
	       p2_off < p2->pack->num_objects * p2_step)
	{
		const int cmp = hashcmp(p1_base + p1_off, p2_base + p2_off);
		/* cmp ~ p1 - p2 */
		if (cmp == 0) {
			p1_hint = llist_sorted_remove(p1->unique_objects,
					(const struct object_id *)(p1_base + p1_off),
					p1_hint);
			p2_hint = llist_sorted_remove(p2->unique_objects,
					(const struct object_id *)(p1_base + p1_off),
					p2_hint);
			p1_off += p1_step;
			p2_off += p2_step;
			continue;
		}
		if (cmp < 0) { /* p1 has the object, p2 doesn't */
			p1_off += p1_step;
		} else { /* p2 has the object, p1 doesn't */
			p2_off += p2_step;
		}
	}
}