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
struct refspec_item {char* dst; } ;
struct object_id {int dummy; } ;
struct known_remote {int /*<<< orphan*/  remote; struct known_remote* next; } ;
struct branches_for_remote {int /*<<< orphan*/  branches; int /*<<< orphan*/  skipped; TYPE_1__* keep; int /*<<< orphan*/  remote; } ;
typedef  int /*<<< orphan*/  refspec ;
struct TYPE_2__ {struct known_remote* list; } ;

/* Variables and functions */
 char const* abbrev_branch (char const*) ; 
 int /*<<< orphan*/  memset (struct refspec_item*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ remote_find_tracking (int /*<<< orphan*/ ,struct refspec_item*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int add_branch_for_removal(const char *refname,
	const struct object_id *oid, int flags, void *cb_data)
{
	struct branches_for_remote *branches = cb_data;
	struct refspec_item refspec;
	struct known_remote *kr;

	memset(&refspec, 0, sizeof(refspec));
	refspec.dst = (char *)refname;
	if (remote_find_tracking(branches->remote, &refspec))
		return 0;

	/* don't delete a branch if another remote also uses it */
	for (kr = branches->keep->list; kr; kr = kr->next) {
		memset(&refspec, 0, sizeof(refspec));
		refspec.dst = (char *)refname;
		if (!remote_find_tracking(kr->remote, &refspec))
			return 0;
	}

	/* don't delete non-remote-tracking refs */
	if (!starts_with(refname, "refs/remotes/")) {
		/* advise user how to delete local branches */
		if (starts_with(refname, "refs/heads/"))
			string_list_append(branches->skipped,
					   abbrev_branch(refname));
		/* silently skip over other non-remote refs */
		return 0;
	}

	string_list_append(branches->branches, refname);

	return 0;
}