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
struct merge_options {char const* branch1; TYPE_1__* repo; scalar_t__ call_depth; } ;
struct diff_filespec {int /*<<< orphan*/ * path; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct diff_filepair {struct diff_filespec* two; struct diff_filespec* one; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ handle_change_delete (struct merge_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int remove_file_from_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int update_stages (struct merge_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct diff_filespec const*,struct diff_filespec const*) ; 

__attribute__((used)) static int handle_rename_delete(struct merge_options *o,
				struct diff_filepair *pair,
				const char *rename_branch,
				const char *delete_branch)
{
	const struct diff_filespec *orig = pair->one;
	const struct diff_filespec *dest = pair->two;

	if (handle_change_delete(o,
				 o->call_depth ? orig->path : dest->path,
				 o->call_depth ? NULL : orig->path,
				 &orig->oid, orig->mode,
				 &dest->oid, dest->mode,
				 rename_branch, delete_branch,
				 _("rename"), _("renamed")))
		return -1;

	if (o->call_depth)
		return remove_file_from_index(o->repo->index, dest->path);
	else
		return update_stages(o, dest->path, NULL,
				     rename_branch == o->branch1 ? dest : NULL,
				     rename_branch == o->branch1 ? NULL : dest);
}