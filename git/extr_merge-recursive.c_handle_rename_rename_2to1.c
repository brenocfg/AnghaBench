#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rename_conflict_info {TYPE_7__* ren2; TYPE_6__* ren1; } ;
struct merge_options {TYPE_5__* priv; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; } ;
struct TYPE_17__ {char* path; } ;
struct merge_file_info {TYPE_8__ blob; } ;
struct diff_filespec {char* path; } ;
struct TYPE_16__ {int /*<<< orphan*/  branch; TYPE_4__* src_entry; TYPE_2__* pair; } ;
struct TYPE_15__ {int /*<<< orphan*/  branch; TYPE_3__* src_entry; TYPE_1__* pair; } ;
struct TYPE_14__ {int call_depth; } ;
struct TYPE_13__ {struct diff_filespec* stages; } ;
struct TYPE_12__ {struct diff_filespec* stages; } ;
struct TYPE_11__ {struct diff_filespec* two; struct diff_filespec* one; } ;
struct TYPE_10__ {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_file_collision (struct merge_options*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,TYPE_8__*) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char*,char*) ; 

__attribute__((used)) static int handle_rename_rename_2to1(struct merge_options *opt,
				     struct rename_conflict_info *ci)
{
	/* Two files, a & b, were renamed to the same thing, c. */
	struct diff_filespec *a = ci->ren1->pair->one;
	struct diff_filespec *b = ci->ren2->pair->one;
	struct diff_filespec *c1 = ci->ren1->pair->two;
	struct diff_filespec *c2 = ci->ren2->pair->two;
	char *path = c1->path; /* == c2->path */
	char *path_side_1_desc;
	char *path_side_2_desc;
	struct merge_file_info mfi_c1;
	struct merge_file_info mfi_c2;
	int ostage1, ostage2;

	output(opt, 1, _("CONFLICT (rename/rename): "
	       "Rename %s->%s in %s. "
	       "Rename %s->%s in %s"),
	       a->path, c1->path, ci->ren1->branch,
	       b->path, c2->path, ci->ren2->branch);

	path_side_1_desc = xstrfmt("version of %s from %s", path, a->path);
	path_side_2_desc = xstrfmt("version of %s from %s", path, b->path);
	ostage1 = ci->ren1->branch == opt->branch1 ? 3 : 2;
	ostage2 = ostage1 ^ 1;
	ci->ren1->src_entry->stages[ostage1].path = a->path;
	ci->ren2->src_entry->stages[ostage2].path = b->path;
	if (merge_mode_and_contents(opt, a, c1,
				    &ci->ren1->src_entry->stages[ostage1],
				    path_side_1_desc,
				    opt->branch1, opt->branch2,
				    1 + opt->priv->call_depth * 2, &mfi_c1) ||
	    merge_mode_and_contents(opt, b,
				    &ci->ren2->src_entry->stages[ostage2],
				    c2, path_side_2_desc,
				    opt->branch1, opt->branch2,
				    1 + opt->priv->call_depth * 2, &mfi_c2))
		return -1;
	free(path_side_1_desc);
	free(path_side_2_desc);
	mfi_c1.blob.path = path;
	mfi_c2.blob.path = path;

	return handle_file_collision(opt, path, a->path, b->path,
				     ci->ren1->branch, ci->ren2->branch,
				     &mfi_c1.blob, &mfi_c2.blob);
}