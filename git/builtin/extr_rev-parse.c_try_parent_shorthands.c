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
struct object_id {int dummy; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {struct object_id oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  REVERSED ; 
 int commit_list_count (struct commit_list*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid_committish (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  show_rev (int /*<<< orphan*/ ,struct object_id*,char const*) ; 
 char* strstr (char const*,char*) ; 
 int strtoul (char*,char**,int) ; 
 scalar_t__ symbolic ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrfmt (char*,char const*,int) ; 

__attribute__((used)) static int try_parent_shorthands(const char *arg)
{
	char *dotdot;
	struct object_id oid;
	struct commit *commit;
	struct commit_list *parents;
	int parent_number;
	int include_rev = 0;
	int include_parents = 0;
	int exclude_parent = 0;

	if ((dotdot = strstr(arg, "^!"))) {
		include_rev = 1;
		if (dotdot[2])
			return 0;
	} else if ((dotdot = strstr(arg, "^@"))) {
		include_parents = 1;
		if (dotdot[2])
			return 0;
	} else if ((dotdot = strstr(arg, "^-"))) {
		include_rev = 1;
		exclude_parent = 1;

		if (dotdot[2]) {
			char *end;
			exclude_parent = strtoul(dotdot + 2, &end, 10);
			if (*end != '\0' || !exclude_parent)
				return 0;
		}
	} else
		return 0;

	*dotdot = 0;
	if (get_oid_committish(arg, &oid) ||
	    !(commit = lookup_commit_reference(the_repository, &oid))) {
		*dotdot = '^';
		return 0;
	}

	if (exclude_parent &&
	    exclude_parent > commit_list_count(commit->parents)) {
		*dotdot = '^';
		return 0;
	}

	if (include_rev)
		show_rev(NORMAL, &oid, arg);
	for (parents = commit->parents, parent_number = 1;
	     parents;
	     parents = parents->next, parent_number++) {
		char *name = NULL;

		if (exclude_parent && parent_number != exclude_parent)
			continue;

		if (symbolic)
			name = xstrfmt("%s^%d", arg, parent_number);
		show_rev(include_parents ? NORMAL : REVERSED,
			 &parents->item->object.oid, name);
		free(name);
	}

	*dotdot = '^';
	return 1;
}