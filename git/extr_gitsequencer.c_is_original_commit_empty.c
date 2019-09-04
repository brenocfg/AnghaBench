#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_2__ object; TYPE_1__* parents; } ;
struct TYPE_6__ {struct object_id* empty_tree; } ;
struct TYPE_4__ {struct commit* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object_id* get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int oideq (struct object_id const*,struct object_id*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 TYPE_3__* the_hash_algo ; 

__attribute__((used)) static int is_original_commit_empty(struct commit *commit)
{
	const struct object_id *ptree_oid;

	if (parse_commit(commit))
		return error(_("could not parse commit %s"),
			     oid_to_hex(&commit->object.oid));
	if (commit->parents) {
		struct commit *parent = commit->parents->item;
		if (parse_commit(parent))
			return error(_("could not parse parent commit %s"),
				oid_to_hex(&parent->object.oid));
		ptree_oid = get_commit_tree_oid(parent);
	} else {
		ptree_oid = the_hash_algo->empty_tree; /* commit is root */
	}

	return oideq(ptree_oid, get_commit_tree_oid(commit));
}