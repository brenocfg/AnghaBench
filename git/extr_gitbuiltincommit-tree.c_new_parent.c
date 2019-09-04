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
struct object_id {int dummy; } ;
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct TYPE_2__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 

__attribute__((used)) static void new_parent(struct commit *parent, struct commit_list **parents_p)
{
	struct object_id *oid = &parent->object.oid;
	struct commit_list *parents;
	for (parents = *parents_p; parents; parents = parents->next) {
		if (parents->item == parent) {
			error(_("duplicate parent %s ignored"), oid_to_hex(oid));
			return;
		}
		parents_p = &parents->next;
	}
	commit_list_insert(parent, parents_p);
}