#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct island_bitmap {int dummy; } ;
struct commit_list {TYPE_1__* item; struct commit_list* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  hash; } ;
struct TYPE_7__ {TYPE_2__ oid; } ;
struct commit {struct commit_list* parents; TYPE_3__ object; } ;
typedef  scalar_t__ khiter_t ;
struct TYPE_8__ {int /*<<< orphan*/  object; } ;
struct TYPE_5__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 TYPE_4__* get_commit_tree (struct commit*) ; 
 int /*<<< orphan*/  island_marks ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_sha1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct island_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 int /*<<< orphan*/  set_island_marks (int /*<<< orphan*/ *,struct island_bitmap*) ; 

void propagate_island_marks(struct commit *commit)
{
	khiter_t pos = kh_get_sha1(island_marks, commit->object.oid.hash);

	if (pos < kh_end(island_marks)) {
		struct commit_list *p;
		struct island_bitmap *root_marks = kh_value(island_marks, pos);

		parse_commit(commit);
		set_island_marks(&get_commit_tree(commit)->object, root_marks);
		for (p = commit->parents; p; p = p->next)
			set_island_marks(&p->item->object, root_marks);
	}
}