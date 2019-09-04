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
struct rename_conflict_info {TYPE_3__* dst_entry1; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; int /*<<< orphan*/  ren1_other; TYPE_1__* pair1; } ;
struct merge_options {int call_depth; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; } ;
struct merge_file_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct diff_filespec {char* path; } ;
struct TYPE_6__ {TYPE_2__* stages; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_file_collision (struct merge_options*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char*,char*) ; 

__attribute__((used)) static int handle_rename_add(struct merge_options *o,
			     struct rename_conflict_info *ci)
{
	/* a was renamed to c, and a separate c was added. */
	struct diff_filespec *a = ci->pair1->one;
	struct diff_filespec *c = ci->pair1->two;
	char *path = c->path;
	char *prev_path_desc;
	struct merge_file_info mfi;

	int other_stage = (ci->branch1 == o->branch1 ? 3 : 2);

	output(o, 1, _("CONFLICT (rename/add): "
	       "Rename %s->%s in %s.  Added %s in %s"),
	       a->path, c->path, ci->branch1,
	       c->path, ci->branch2);

	prev_path_desc = xstrfmt("version of %s from %s", path, a->path);
	if (merge_mode_and_contents(o, a, c, &ci->ren1_other, prev_path_desc,
				    o->branch1, o->branch2,
				    1 + o->call_depth * 2, &mfi))
		return -1;
	free(prev_path_desc);

	return handle_file_collision(o,
				     c->path, a->path, NULL,
				     ci->branch1, ci->branch2,
				     &mfi.oid, mfi.mode,
				     &ci->dst_entry1->stages[other_stage].oid,
				     ci->dst_entry1->stages[other_stage].mode);
}