#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rev_cmdline_info {int nr; struct rev_cmdline_entry* rev; } ;
struct rev_cmdline_entry {int flags; TYPE_2__* item; int /*<<< orphan*/  name; } ;
struct object_id {int dummy; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct TYPE_9__ {scalar_t__ nr; } ;
struct TYPE_8__ {struct commit* util; } ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
#define  OBJ_BLOB 129 
#define  OBJ_COMMIT 128 
 scalar_t__ OBJ_TAG ; 
 int UNINTERESTING ; 
 char* apply_refspecs (TYPE_4__*,char*) ; 
 int dwim_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  export_blob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extra_refs ; 
 int /*<<< orphan*/  free (char*) ; 
 struct commit* get_commit (struct rev_cmdline_entry*,char*) ; 
 TYPE_4__ refspecs ; 
 int /*<<< orphan*/  revision_sources ; 
 char** revision_sources_at (int /*<<< orphan*/ *,struct commit*) ; 
 TYPE_3__* string_list_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_list_remove_duplicates (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_name (int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void get_tags_and_duplicates(struct rev_cmdline_info *info)
{
	int i;

	for (i = 0; i < info->nr; i++) {
		struct rev_cmdline_entry *e = info->rev + i;
		struct object_id oid;
		struct commit *commit;
		char *full_name;

		if (e->flags & UNINTERESTING)
			continue;

		if (dwim_ref(e->name, strlen(e->name), &oid, &full_name) != 1)
			continue;

		if (refspecs.nr) {
			char *private;
			private = apply_refspecs(&refspecs, full_name);
			if (private) {
				free(full_name);
				full_name = private;
			}
		}

		commit = get_commit(e, full_name);
		if (!commit) {
			warning("%s: Unexpected object of type %s, skipping.",
				e->name,
				type_name(e->item->type));
			continue;
		}

		switch(commit->object.type) {
		case OBJ_COMMIT:
			break;
		case OBJ_BLOB:
			export_blob(&commit->object.oid);
			continue;
		default: /* OBJ_TAG (nested tags) is already handled */
			warning("Tag points to object of unexpected type %s, skipping.",
				type_name(commit->object.type));
			continue;
		}

		/*
		 * Make sure this ref gets properly updated eventually, whether
		 * through a commit or manually at the end.
		 */
		if (e->item->type != OBJ_TAG)
			string_list_append(&extra_refs, full_name)->util = commit;

		if (!*revision_sources_at(&revision_sources, commit))
			*revision_sources_at(&revision_sources, commit) = full_name;
	}

	string_list_sort(&extra_refs);
	string_list_remove_duplicates(&extra_refs, 0);
}