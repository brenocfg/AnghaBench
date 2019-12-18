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
struct object_list {struct object_list* next; struct object* item; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct object {TYPE_1__ oid; } ;
struct bitmap_index {int /*<<< orphan*/  pack; } ;

/* Variables and functions */
 scalar_t__ find_pack_entry_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in_bitmapped_pack(struct bitmap_index *bitmap_git,
			     struct object_list *roots)
{
	while (roots) {
		struct object *object = roots->item;
		roots = roots->next;

		if (find_pack_entry_one(object->oid.hash, bitmap_git->pack) > 0)
			return 1;
	}

	return 0;
}