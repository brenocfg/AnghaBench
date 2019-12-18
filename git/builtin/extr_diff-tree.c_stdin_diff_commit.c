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
struct commit_list {int dummy; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_2__ {struct commit_list* next; } ;

/* Variables and functions */
 TYPE_1__* commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int log_tree_commit (int /*<<< orphan*/ *,struct commit*) ; 
 int /*<<< orphan*/  log_tree_opt ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int stdin_diff_commit(struct commit *commit, const char *p)
{
	struct object_id oid;
	struct commit_list **pptr = NULL;

	/* Graft the fake parents locally to the commit */
	while (isspace(*p++) && !parse_oid_hex(p, &oid, &p)) {
		struct commit *parent = lookup_commit(the_repository, &oid);
		if (!pptr) {
			/* Free the real parent list */
			free_commit_list(commit->parents);
			commit->parents = NULL;
			pptr = &(commit->parents);
		}
		if (parent) {
			pptr = &commit_list_insert(parent, pptr)->next;
		}
	}
	return log_tree_commit(&log_tree_opt, commit);
}