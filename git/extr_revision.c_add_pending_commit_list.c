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
struct rev_info {int dummy; } ;
struct object {unsigned int flags; int /*<<< orphan*/  oid; } ;
struct commit_list {struct commit_list* next; TYPE_1__* item; } ;
struct TYPE_2__ {struct object object; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_pending_commit_list(struct rev_info *revs,
				    struct commit_list *commit_list,
				    unsigned int flags)
{
	while (commit_list) {
		struct object *object = &commit_list->item->object;
		object->flags |= flags;
		add_pending_object(revs, object, oid_to_hex(&object->oid));
		commit_list = commit_list->next;
	}
}