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
struct repository {TYPE_1__* objects; } ;
struct packed_git {scalar_t__ num_objects; struct packed_git* next; } ;
struct multi_pack_index {scalar_t__ num_objects; struct multi_pack_index* next; } ;
struct TYPE_2__ {unsigned long approximate_object_count; struct packed_git* packed_git; int /*<<< orphan*/  approximate_object_count_valid; } ;

/* Variables and functions */
 struct multi_pack_index* get_multi_pack_index (struct repository*) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  prepare_packed_git (struct repository*) ; 

unsigned long repo_approximate_object_count(struct repository *r)
{
	if (!r->objects->approximate_object_count_valid) {
		unsigned long count;
		struct multi_pack_index *m;
		struct packed_git *p;

		prepare_packed_git(r);
		count = 0;
		for (m = get_multi_pack_index(r); m; m = m->next)
			count += m->num_objects;
		for (p = r->objects->packed_git; p; p = p->next) {
			if (open_pack_index(p))
				continue;
			count += p->num_objects;
		}
		r->objects->approximate_object_count = count;
	}
	return r->objects->approximate_object_count;
}