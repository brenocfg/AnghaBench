#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rename_conflict_info {TYPE_5__* ren1; } ;
struct merge_options {char const* branch1; char* branch2; TYPE_3__* priv; } ;
struct TYPE_15__ {char* path; } ;
struct merge_file_info {TYPE_7__ blob; } ;
struct diff_filespec {char* path; } ;
struct TYPE_16__ {char* path; } ;
struct TYPE_14__ {char* path; } ;
struct TYPE_13__ {char* branch; TYPE_4__* dst_entry; TYPE_2__* src_entry; TYPE_1__* pair; } ;
struct TYPE_12__ {TYPE_8__* stages; } ;
struct TYPE_11__ {int call_depth; } ;
struct TYPE_10__ {TYPE_6__* stages; } ;
struct TYPE_9__ {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_file_collision (struct merge_options*,char*,char*,int /*<<< orphan*/ *,char const*,char const*,TYPE_7__*,TYPE_8__*) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,TYPE_6__*,char*,char*,char*,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*,char const*,char*,char const*) ; 
 char* xstrfmt (char*,char*,char*) ; 

__attribute__((used)) static int handle_rename_add(struct merge_options *opt,
			     struct rename_conflict_info *ci)
{
	/* a was renamed to c, and a separate c was added. */
	struct diff_filespec *a = ci->ren1->pair->one;
	struct diff_filespec *c = ci->ren1->pair->two;
	char *path = c->path;
	char *prev_path_desc;
	struct merge_file_info mfi;

	const char *rename_branch = ci->ren1->branch;
	const char *add_branch = (opt->branch1 == rename_branch ?
				  opt->branch2 : opt->branch1);
	int other_stage = (ci->ren1->branch == opt->branch1 ? 3 : 2);

	output(opt, 1, _("CONFLICT (rename/add): "
	       "Rename %s->%s in %s.  Added %s in %s"),
	       a->path, c->path, rename_branch,
	       c->path, add_branch);

	prev_path_desc = xstrfmt("version of %s from %s", path, a->path);
	ci->ren1->src_entry->stages[other_stage].path = a->path;
	if (merge_mode_and_contents(opt, a, c,
				    &ci->ren1->src_entry->stages[other_stage],
				    prev_path_desc,
				    opt->branch1, opt->branch2,
				    1 + opt->priv->call_depth * 2, &mfi))
		return -1;
	free(prev_path_desc);

	ci->ren1->dst_entry->stages[other_stage].path = mfi.blob.path = c->path;
	return handle_file_collision(opt,
				     c->path, a->path, NULL,
				     rename_branch, add_branch,
				     &mfi.blob,
				     &ci->ren1->dst_entry->stages[other_stage]);
}