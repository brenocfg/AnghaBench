#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int log_tree_commit (int /*<<< orphan*/ *,struct commit*) ; 
 int /*<<< orphan*/  log_tree_opt ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int diff_tree_commit_oid(const struct object_id *oid)
{
	struct commit *commit = lookup_commit_reference(the_repository, oid);
	if (!commit)
		return -1;
	return log_tree_commit(&log_tree_opt, commit);
}