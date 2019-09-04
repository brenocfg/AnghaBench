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
struct diff_filespec {char* path; } ;
struct rename_conflict_info {int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; struct diff_filespec ren2_other; struct diff_filespec ren1_other; TYPE_2__* pair2; TYPE_1__* pair1; } ;
struct merge_options {int call_depth; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; } ;
struct merge_file_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {struct diff_filespec* two; struct diff_filespec* one; } ;
struct TYPE_3__ {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_file_collision (struct merge_options*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char*,char*) ; 

__attribute__((used)) static int handle_rename_rename_2to1(struct merge_options *o,
				     struct rename_conflict_info *ci)
{
	/* Two files, a & b, were renamed to the same thing, c. */
	struct diff_filespec *a = ci->pair1->one;
	struct diff_filespec *b = ci->pair2->one;
	struct diff_filespec *c1 = ci->pair1->two;
	struct diff_filespec *c2 = ci->pair2->two;
	char *path = c1->path; /* == c2->path */
	char *path_side_1_desc;
	char *path_side_2_desc;
	struct merge_file_info mfi_c1;
	struct merge_file_info mfi_c2;

	output(o, 1, _("CONFLICT (rename/rename): "
	       "Rename %s->%s in %s. "
	       "Rename %s->%s in %s"),
	       a->path, c1->path, ci->branch1,
	       b->path, c2->path, ci->branch2);

	path_side_1_desc = xstrfmt("version of %s from %s", path, a->path);
	path_side_2_desc = xstrfmt("version of %s from %s", path, b->path);
	if (merge_mode_and_contents(o, a, c1, &ci->ren1_other, path_side_1_desc,
				    o->branch1, o->branch2,
				    1 + o->call_depth * 2, &mfi_c1) ||
	    merge_mode_and_contents(o, b, &ci->ren2_other, c2, path_side_2_desc,
				    o->branch1, o->branch2,
				    1 + o->call_depth * 2, &mfi_c2))
		return -1;
	free(path_side_1_desc);
	free(path_side_2_desc);

	return handle_file_collision(o, path, a->path, b->path,
				     ci->branch1, ci->branch2,
				     &mfi_c1.oid, mfi_c1.mode,
				     &mfi_c2.oid, mfi_c2.mode);
}