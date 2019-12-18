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
struct tree {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct merge_options {int repo; int detect_renames; scalar_t__ detect_directory_renames; int rename_limit; scalar_t__ rename_score; int show_rename_progress; scalar_t__ xdl_opts; scalar_t__ recursive_variant; int verbosity; int buffer_output; TYPE_2__* priv; TYPE_1__ obuf; scalar_t__ branch2; scalar_t__ branch1; } ;
struct TYPE_4__ {int /*<<< orphan*/  df_conflict_file_set; } ;

/* Variables and functions */
 int DIFF_DETECT_COPY ; 
 scalar_t__ MAX_SCORE ; 
 scalar_t__ MERGE_DIRECTORY_RENAMES_NONE ; 
 scalar_t__ MERGE_DIRECTORY_RENAMES_TRUE ; 
 scalar_t__ MERGE_VARIANT_NORMAL ; 
 scalar_t__ MERGE_VARIANT_THEIRS ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_index_has_changes (int,struct tree*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* xcalloc (int,int) ; 

__attribute__((used)) static int merge_start(struct merge_options *opt, struct tree *head)
{
	struct strbuf sb = STRBUF_INIT;

	/* Sanity checks on opt */
	assert(opt->repo);

	assert(opt->branch1 && opt->branch2);

	assert(opt->detect_renames >= -1 &&
	       opt->detect_renames <= DIFF_DETECT_COPY);
	assert(opt->detect_directory_renames >= MERGE_DIRECTORY_RENAMES_NONE &&
	       opt->detect_directory_renames <= MERGE_DIRECTORY_RENAMES_TRUE);
	assert(opt->rename_limit >= -1);
	assert(opt->rename_score >= 0 && opt->rename_score <= MAX_SCORE);
	assert(opt->show_rename_progress >= 0 && opt->show_rename_progress <= 1);

	assert(opt->xdl_opts >= 0);
	assert(opt->recursive_variant >= MERGE_VARIANT_NORMAL &&
	       opt->recursive_variant <= MERGE_VARIANT_THEIRS);

	assert(opt->verbosity >= 0 && opt->verbosity <= 5);
	assert(opt->buffer_output <= 2);
	assert(opt->obuf.len == 0);

	assert(opt->priv == NULL);

	/* Sanity check on repo state; index must match head */
	if (repo_index_has_changes(opt->repo, head, &sb)) {
		err(opt, _("Your local changes to the following files would be overwritten by merge:\n  %s"),
		    sb.buf);
		strbuf_release(&sb);
		return -1;
	}

	opt->priv = xcalloc(1, sizeof(*opt->priv));
	string_list_init(&opt->priv->df_conflict_file_set, 1);
	return 0;
}