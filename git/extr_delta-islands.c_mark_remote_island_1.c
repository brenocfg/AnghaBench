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
typedef  size_t uint32_t ;
struct tag {struct object* tagged; } ;
struct repository {int dummy; } ;
struct TYPE_2__ {size_t nr; int /*<<< orphan*/ * oid; } ;
struct remote_island {TYPE_1__ oids; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  oid; int /*<<< orphan*/  flags; } ;
struct island_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDS_BITMAP ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 struct island_bitmap* create_or_get_island_marks (struct object*) ; 
 int /*<<< orphan*/  island_bitmap_set (struct island_bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  island_counter ; 
 int /*<<< orphan*/  island_counter_core ; 
 struct object* parse_object (struct repository*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_remote_island_1(struct repository *r,
				 struct remote_island *rl,
				 int is_core_island)
{
	uint32_t i;

	for (i = 0; i < rl->oids.nr; ++i) {
		struct island_bitmap *marks;
		struct object *obj = parse_object(r, &rl->oids.oid[i]);

		if (!obj)
			continue;

		marks = create_or_get_island_marks(obj);
		island_bitmap_set(marks, island_counter);

		if (is_core_island && obj->type == OBJ_COMMIT)
			obj->flags |= NEEDS_BITMAP;

		/* If it was a tag, also make sure we hit the underlying object. */
		while (obj && obj->type == OBJ_TAG) {
			obj = ((struct tag *)obj)->tagged;
			if (obj) {
				parse_object(r, &obj->oid);
				marks = create_or_get_island_marks(obj);
				island_bitmap_set(marks, island_counter);
			}
		}
	}

	if (is_core_island)
		island_counter_core = island_counter;

	island_counter++;
}