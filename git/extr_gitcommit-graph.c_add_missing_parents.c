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
struct packed_oid_list {int nr; int /*<<< orphan*/ * list; int /*<<< orphan*/  alloc; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_missing_parents(struct packed_oid_list *oids, struct commit *commit)
{
	struct commit_list *parent;
	for (parent = commit->parents; parent; parent = parent->next) {
		if (!(parent->item->object.flags & UNINTERESTING)) {
			ALLOC_GROW(oids->list, oids->nr + 1, oids->alloc);
			oidcpy(&oids->list[oids->nr], &(parent->item->object.oid));
			oids->nr++;
			parent->item->object.flags |= UNINTERESTING;
		}
	}
}