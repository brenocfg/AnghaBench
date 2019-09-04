#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct packed_git {scalar_t__ num_objects; struct packed_git* next; } ;
struct multi_pack_index {scalar_t__ num_objects; struct multi_pack_index* next; } ;
struct TYPE_6__ {TYPE_1__* objects; } ;
struct TYPE_5__ {unsigned long approximate_object_count; struct packed_git* packed_git; int /*<<< orphan*/  approximate_object_count_valid; } ;

/* Variables and functions */
 struct multi_pack_index* get_multi_pack_index (TYPE_2__*) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  prepare_packed_git (TYPE_2__*) ; 
 TYPE_2__* the_repository ; 

unsigned long approximate_object_count(void)
{
	if (!the_repository->objects->approximate_object_count_valid) {
		unsigned long count;
		struct multi_pack_index *m;
		struct packed_git *p;

		prepare_packed_git(the_repository);
		count = 0;
		for (m = get_multi_pack_index(the_repository); m; m = m->next)
			count += m->num_objects;
		for (p = the_repository->objects->packed_git; p; p = p->next) {
			if (open_pack_index(p))
				continue;
			count += p->num_objects;
		}
		the_repository->objects->approximate_object_count = count;
	}
	return the_repository->objects->approximate_object_count;
}