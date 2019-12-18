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
struct option {struct commit_list** value; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG_NOARG (int,char const*) ; 
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert_oid_type (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_oid_commit (char const*,struct object_id*) ; 
 int /*<<< orphan*/  lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  new_parent (int /*<<< orphan*/ ,struct commit_list**) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int parse_parent_arg_callback(const struct option *opt,
		const char *arg, int unset)
{
	struct object_id oid;
	struct commit_list **parents = opt->value;

	BUG_ON_OPT_NEG_NOARG(unset, arg);

	if (get_oid_commit(arg, &oid))
		die(_("not a valid object name %s"), arg);

	assert_oid_type(&oid, OBJ_COMMIT);
	new_parent(lookup_commit(the_repository, &oid), parents);
	return 0;
}