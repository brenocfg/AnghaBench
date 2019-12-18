#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_pool ;
typedef  scalar_t__ git_iterator_type_t ;
struct TYPE_14__ {int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_2__ git_diff_options ;
struct TYPE_17__ {int flags; int context_lines; scalar_t__ ignore_submodules; char const* old_prefix; char const* new_prefix; } ;
struct TYPE_13__ {scalar_t__ old_src; scalar_t__ new_src; TYPE_5__ opts; int /*<<< orphan*/  pool; int /*<<< orphan*/ * repo; } ;
struct TYPE_15__ {TYPE_1__ base; int /*<<< orphan*/  diffcaps; int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_3__ git_diff_generated ;
struct TYPE_16__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int DIFF_FLAG_IS_SET (TYPE_3__*,int) ; 
 int /*<<< orphan*/  DIFF_FLAG_SET (TYPE_3__*,int,int) ; 
 char* DIFF_NEW_PREFIX_DEFAULT ; 
 char* DIFF_OLD_PREFIX_DEFAULT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_FILEMODE ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_IGNORESTAT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_TRUSTCTIME ; 
 int /*<<< orphan*/  GIT_DIFFCAPS_HAS_SYMLINKS ; 
 int /*<<< orphan*/  GIT_DIFFCAPS_IGNORE_STAT ; 
 int /*<<< orphan*/  GIT_DIFFCAPS_TRUST_CTIME ; 
 int /*<<< orphan*/  GIT_DIFFCAPS_TRUST_MODE_BITS ; 
 int GIT_DIFF_IGNORE_CASE ; 
 int GIT_DIFF_IGNORE_FILEMODE ; 
 int GIT_DIFF_INCLUDE_TYPECHANGE ; 
 int GIT_DIFF_INCLUDE_TYPECHANGE_TREES ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 int GIT_DIFF_REVERSE ; 
 int GIT_DIFF_SHOW_UNTRACKED_CONTENT ; 
 int GIT_DIFF_UPDATE_INDEX ; 
 scalar_t__ GIT_ITERATOR_TYPE_INDEX ; 
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 char* diff_mnemonic_prefix (scalar_t__,int) ; 
 void* diff_strdup_prefix (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config__get_bool_force (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_config__get_int_force (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config__lookup_entry (TYPE_4__**,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_pathspec__vinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_parse_ignore (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int diff_generated_apply_options(
	git_diff_generated *diff,
	const git_diff_options *opts)
{
	git_config *cfg = NULL;
	git_repository *repo = diff->base.repo;
	git_pool *pool = &diff->base.pool;
	int val;

	if (opts) {
		/* copy user options (except case sensitivity info from iterators) */
		bool icase = DIFF_FLAG_IS_SET(diff, GIT_DIFF_IGNORE_CASE);
		memcpy(&diff->base.opts, opts, sizeof(diff->base.opts));
		DIFF_FLAG_SET(diff, GIT_DIFF_IGNORE_CASE, icase);

		/* initialize pathspec from options */
		if (git_pathspec__vinit(&diff->pathspec, &opts->pathspec, pool) < 0)
			return -1;
	}

	/* flag INCLUDE_TYPECHANGE_TREES implies INCLUDE_TYPECHANGE */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_INCLUDE_TYPECHANGE_TREES))
		diff->base.opts.flags |= GIT_DIFF_INCLUDE_TYPECHANGE;

	/* flag INCLUDE_UNTRACKED_CONTENT implies INCLUDE_UNTRACKED */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_SHOW_UNTRACKED_CONTENT))
		diff->base.opts.flags |= GIT_DIFF_INCLUDE_UNTRACKED;

	/* load config values that affect diff behavior */
	if ((val = git_repository_config_snapshot(&cfg, repo)) < 0)
		return val;

	if (!git_config__configmap_lookup(&val, cfg, GIT_CONFIGMAP_SYMLINKS) && val)
		diff->diffcaps |= GIT_DIFFCAPS_HAS_SYMLINKS;

	if (!git_config__configmap_lookup(&val, cfg, GIT_CONFIGMAP_IGNORESTAT) && val)
		diff->diffcaps |= GIT_DIFFCAPS_IGNORE_STAT;

	if ((diff->base.opts.flags & GIT_DIFF_IGNORE_FILEMODE) == 0 &&
		!git_config__configmap_lookup(&val, cfg, GIT_CONFIGMAP_FILEMODE) && val)
		diff->diffcaps |= GIT_DIFFCAPS_TRUST_MODE_BITS;

	if (!git_config__configmap_lookup(&val, cfg, GIT_CONFIGMAP_TRUSTCTIME) && val)
		diff->diffcaps |= GIT_DIFFCAPS_TRUST_CTIME;

	/* Don't set GIT_DIFFCAPS_USE_DEV - compile time option in core git */

	/* If not given explicit `opts`, check `diff.xyz` configs */
	if (!opts) {
		int context = git_config__get_int_force(cfg, "diff.context", 3);
		diff->base.opts.context_lines = context >= 0 ? (uint32_t)context : 3;

		/* add other defaults here */
	}

	/* Reverse src info if diff is reversed */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_REVERSE)) {
		git_iterator_type_t tmp_src = diff->base.old_src;
		diff->base.old_src = diff->base.new_src;
		diff->base.new_src = tmp_src;
	}

	/* Unset UPDATE_INDEX unless diffing workdir and index */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_UPDATE_INDEX) &&
		(!(diff->base.old_src == GIT_ITERATOR_TYPE_WORKDIR ||
		   diff->base.new_src == GIT_ITERATOR_TYPE_WORKDIR) ||
		 !(diff->base.old_src == GIT_ITERATOR_TYPE_INDEX ||
		   diff->base.new_src == GIT_ITERATOR_TYPE_INDEX)))
		diff->base.opts.flags &= ~GIT_DIFF_UPDATE_INDEX;

	/* if ignore_submodules not explicitly set, check diff config */
	if (diff->base.opts.ignore_submodules <= 0) {
		 git_config_entry *entry;
		git_config__lookup_entry(&entry, cfg, "diff.ignoresubmodules", true);

		if (entry && git_submodule_parse_ignore(
				&diff->base.opts.ignore_submodules, entry->value) < 0)
			git_error_clear();
		git_config_entry_free(entry);
	}

	/* if either prefix is not set, figure out appropriate value */
	if (!diff->base.opts.old_prefix || !diff->base.opts.new_prefix) {
		const char *use_old = DIFF_OLD_PREFIX_DEFAULT;
		const char *use_new = DIFF_NEW_PREFIX_DEFAULT;

		if (git_config__get_bool_force(cfg, "diff.noprefix", 0))
			use_old = use_new = "";
		else if (git_config__get_bool_force(cfg, "diff.mnemonicprefix", 0)) {
			use_old = diff_mnemonic_prefix(diff->base.old_src, true);
			use_new = diff_mnemonic_prefix(diff->base.new_src, false);
		}

		if (!diff->base.opts.old_prefix)
			diff->base.opts.old_prefix = use_old;
		if (!diff->base.opts.new_prefix)
			diff->base.opts.new_prefix = use_new;
	}

	/* strdup prefix from pool so we're not dependent on external data */
	diff->base.opts.old_prefix = diff_strdup_prefix(pool, diff->base.opts.old_prefix);
	diff->base.opts.new_prefix = diff_strdup_prefix(pool, diff->base.opts.new_prefix);

	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_REVERSE)) {
		const char *tmp_prefix = diff->base.opts.old_prefix;
		diff->base.opts.old_prefix  = diff->base.opts.new_prefix;
		diff->base.opts.new_prefix  = tmp_prefix;
	}

	git_config_free(cfg);

	/* check strdup results for error */
	return (!diff->base.opts.old_prefix || !diff->base.opts.new_prefix) ? -1 : 0;
}