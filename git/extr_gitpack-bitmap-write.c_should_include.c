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
struct object {int dummy; } ;
struct commit_list {struct commit_list* next; TYPE_2__* item; } ;
struct commit {struct commit_list* parents; } ;
struct bitmap {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEN ; 
 int /*<<< orphan*/  add_to_include_set (struct bitmap*,struct commit*) ; 
 int /*<<< orphan*/  mark_as_seen (struct object*) ; 

__attribute__((used)) static int
should_include(struct commit *commit, void *_data)
{
	struct bitmap *base = _data;

	if (!add_to_include_set(base, commit)) {
		struct commit_list *parent = commit->parents;

		mark_as_seen((struct object *)commit);

		while (parent) {
			parent->item->object.flags |= SEEN;
			mark_as_seen((struct object *)parent->item);
			parent = parent->next;
		}

		return 0;
	}

	return 1;
}