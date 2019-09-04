#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct TYPE_12__ {TYPE_3__* items; } ;
struct TYPE_8__ {int recursive; int find_copies_harder; } ;
struct diff_options {int found_follow; TYPE_5__ pathspec; int /*<<< orphan*/  rename_score; int /*<<< orphan*/  break_opt; int /*<<< orphan*/  single_follow; int /*<<< orphan*/  output_format; TYPE_1__ flags; int /*<<< orphan*/  repo; } ;
struct diff_filepair {char status; TYPE_4__* one; TYPE_2__* two; } ;
struct TYPE_11__ {char* path; } ;
struct TYPE_10__ {int /*<<< orphan*/  match; } ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FORMAT_NO_OUTPUT ; 
 int /*<<< orphan*/  GUARD_PATHSPEC (TYPE_5__*,int) ; 
 int PATHSPEC_ALL_MAGIC ; 
 int PATHSPEC_FROMTOP ; 
 int PATHSPEC_LITERAL ; 
 int /*<<< orphan*/  PATHSPEC_LITERAL_PATH ; 
 int /*<<< orphan*/  clear_pathspec (TYPE_5__*) ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  ll_diff_tree_oid (struct object_id const*,struct object_id const*,struct strbuf*,struct diff_options*) ; 
 int /*<<< orphan*/  parse_pathspec (TYPE_5__*,int,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  repo_diff_setup (int /*<<< orphan*/ ,struct diff_options*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void try_to_follow_renames(const struct object_id *old_oid,
				  const struct object_id *new_oid,
				  struct strbuf *base, struct diff_options *opt)
{
	struct diff_options diff_opts;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_filepair *choice;
	int i;

	/*
	 * follow-rename code is very specific, we need exactly one
	 * path. Magic that matches more than one path is not
	 * supported.
	 */
	GUARD_PATHSPEC(&opt->pathspec, PATHSPEC_FROMTOP | PATHSPEC_LITERAL);
#if 0
	/*
	 * We should reject wildcards as well. Unfortunately we
	 * haven't got a reliable way to detect that 'foo\*bar' in
	 * fact has no wildcards. nowildcard_len is merely a hint for
	 * optimization. Let it slip for now until wildmatch is taught
	 * about dry-run mode and returns wildcard info.
	 */
	if (opt->pathspec.has_wildcard)
		die("BUG:%s:%d: wildcards are not supported",
		    __FILE__, __LINE__);
#endif

	/* Remove the file creation entry from the diff queue, and remember it */
	choice = q->queue[0];
	q->nr = 0;

	repo_diff_setup(opt->repo, &diff_opts);
	diff_opts.flags.recursive = 1;
	diff_opts.flags.find_copies_harder = 1;
	diff_opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_opts.single_follow = opt->pathspec.items[0].match;
	diff_opts.break_opt = opt->break_opt;
	diff_opts.rename_score = opt->rename_score;
	diff_setup_done(&diff_opts);
	ll_diff_tree_oid(old_oid, new_oid, base, &diff_opts);
	diffcore_std(&diff_opts);
	clear_pathspec(&diff_opts.pathspec);

	/* Go through the new set of filepairing, and see if we find a more interesting one */
	opt->found_follow = 0;
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];

		/*
		 * Found a source? Not only do we use that for the new
		 * diff_queued_diff, we will also use that as the path in
		 * the future!
		 */
		if ((p->status == 'R' || p->status == 'C') &&
		    !strcmp(p->two->path, opt->pathspec.items[0].match)) {
			const char *path[2];

			/* Switch the file-pairs around */
			q->queue[i] = choice;
			choice = p;

			/* Update the path we use from now on.. */
			path[0] = p->one->path;
			path[1] = NULL;
			clear_pathspec(&opt->pathspec);
			parse_pathspec(&opt->pathspec,
				       PATHSPEC_ALL_MAGIC & ~PATHSPEC_LITERAL,
				       PATHSPEC_LITERAL_PATH, "", path);

			/*
			 * The caller expects us to return a set of vanilla
			 * filepairs to let a later call to diffcore_std()
			 * it makes to sort the renames out (among other
			 * things), but we already have found renames
			 * ourselves; signal diffcore_std() not to muck with
			 * rename information.
			 */
			opt->found_follow = 1;
			break;
		}
	}

	/*
	 * Then, discard all the non-relevant file pairs...
	 */
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		diff_free_filepair(p);
	}

	/*
	 * .. and re-instate the one we want (which might be either the
	 * original one, or the rename/copy we found)
	 */
	q->queue[0] = choice;
	q->nr = 1;
}