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
struct string_list {int nr; TYPE_1__* items; } ;
struct repository {int dummy; } ;
struct remote {scalar_t__ origin; int /*<<< orphan*/  name; } ;
struct refspec {int dummy; } ;
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 scalar_t__ REMOTE_UNCONFIGURED ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_unpushed_submodules (struct repository*,struct oid_array*,int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  push_submodule (char const*,struct remote const*,struct refspec const*,struct string_list const*,int) ; 
 char* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submodule_push_check (char*,char*,struct remote const*,struct refspec const*) ; 

int push_unpushed_submodules(struct repository *r,
			     struct oid_array *commits,
			     const struct remote *remote,
			     const struct refspec *rs,
			     const struct string_list *push_options,
			     int dry_run)
{
	int i, ret = 1;
	struct string_list needs_pushing = STRING_LIST_INIT_DUP;

	if (!find_unpushed_submodules(r, commits,
				      remote->name, &needs_pushing))
		return 1;

	/*
	 * Verify that the remote and refspec can be propagated to all
	 * submodules.  This check can be skipped if the remote and refspec
	 * won't be propagated due to the remote being unconfigured (e.g. a URL
	 * instead of a remote name).
	 */
	if (remote->origin != REMOTE_UNCONFIGURED) {
		char *head;
		struct object_id head_oid;

		head = resolve_refdup("HEAD", 0, &head_oid, NULL);
		if (!head)
			die(_("Failed to resolve HEAD as a valid ref."));

		for (i = 0; i < needs_pushing.nr; i++)
			submodule_push_check(needs_pushing.items[i].string,
					     head, remote, rs);
		free(head);
	}

	/* Actually push the submodules */
	for (i = 0; i < needs_pushing.nr; i++) {
		const char *path = needs_pushing.items[i].string;
		fprintf(stderr, "Pushing submodule '%s'\n", path);
		if (!push_submodule(path, remote, rs,
				    push_options, dry_run)) {
			fprintf(stderr, "Unable to push submodule '%s'\n", path);
			ret = 0;
		}
	}

	string_list_clear(&needs_pushing, 0);

	return ret;
}