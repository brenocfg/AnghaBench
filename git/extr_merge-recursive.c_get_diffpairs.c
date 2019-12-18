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
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_2__ object; } ;
struct merge_options {scalar_t__ rename_limit; TYPE_3__* priv; int /*<<< orphan*/  show_rename_progress; int /*<<< orphan*/  rename_score; int /*<<< orphan*/  repo; } ;
struct diff_queue_struct {int /*<<< orphan*/ * queue; scalar_t__ nr; } ;
struct TYPE_4__ {int recursive; scalar_t__ rename_empty; } ;
struct diff_options {scalar_t__ detect_rename; int rename_limit; scalar_t__ needed_rename_limit; void* output_format; int /*<<< orphan*/  show_rename_progress; int /*<<< orphan*/  rename_score; TYPE_1__ flags; } ;
struct TYPE_6__ {scalar_t__ needed_rename_limit; } ;

/* Variables and functions */
 scalar_t__ DIFF_DETECT_RENAME ; 
 void* DIFF_FORMAT_NO_OUTPUT ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 scalar_t__ merge_detect_rename (struct merge_options*) ; 
 int /*<<< orphan*/  repo_diff_setup (int /*<<< orphan*/ ,struct diff_options*) ; 
 struct diff_queue_struct* xmalloc (int) ; 

__attribute__((used)) static struct diff_queue_struct *get_diffpairs(struct merge_options *opt,
					       struct tree *o_tree,
					       struct tree *tree)
{
	struct diff_queue_struct *ret;
	struct diff_options opts;

	repo_diff_setup(opt->repo, &opts);
	opts.flags.recursive = 1;
	opts.flags.rename_empty = 0;
	opts.detect_rename = merge_detect_rename(opt);
	/*
	 * We do not have logic to handle the detection of copies.  In
	 * fact, it may not even make sense to add such logic: would we
	 * really want a change to a base file to be propagated through
	 * multiple other files by a merge?
	 */
	if (opts.detect_rename > DIFF_DETECT_RENAME)
		opts.detect_rename = DIFF_DETECT_RENAME;
	opts.rename_limit = (opt->rename_limit >= 0) ? opt->rename_limit : 1000;
	opts.rename_score = opt->rename_score;
	opts.show_rename_progress = opt->show_rename_progress;
	opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_setup_done(&opts);
	diff_tree_oid(&o_tree->object.oid, &tree->object.oid, "", &opts);
	diffcore_std(&opts);
	if (opts.needed_rename_limit > opt->priv->needed_rename_limit)
		opt->priv->needed_rename_limit = opts.needed_rename_limit;

	ret = xmalloc(sizeof(*ret));
	*ret = diff_queued_diff;

	opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_queued_diff.nr = 0;
	diff_queued_diff.queue = NULL;
	diff_flush(&opts);
	return ret;
}