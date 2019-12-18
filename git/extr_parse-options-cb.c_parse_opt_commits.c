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
struct option {int /*<<< orphan*/  value; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,int /*<<< orphan*/ ) ; 
 int error (char*,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  the_repository ; 

int parse_opt_commits(const struct option *opt, const char *arg, int unset)
{
	struct object_id oid;
	struct commit *commit;

	BUG_ON_OPT_NEG(unset);

	if (!arg)
		return -1;
	if (get_oid(arg, &oid))
		return error("malformed object name %s", arg);
	commit = lookup_commit_reference(the_repository, &oid);
	if (!commit)
		return error("no such commit %s", arg);
	commit_list_insert(commit, opt->value);
	return 0;
}