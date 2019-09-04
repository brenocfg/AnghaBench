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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {struct commit_list* next; } ;

/* Variables and functions */
 TYPE_1__* commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference (struct repository*,struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 

__attribute__((used)) static struct commit_list **append_parent(struct repository *r,
					  struct commit_list **tail,
					  const struct object_id *oid)
{
	struct commit *parent;

	parent = lookup_commit_reference(r, oid);
	if (!parent)
		die("no such commit %s", oid_to_hex(oid));
	return &commit_list_insert(parent, tail)->next;
}