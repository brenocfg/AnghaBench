#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int recursive; int find_copies_harder; } ;
struct diff_options {int /*<<< orphan*/  pathspec; TYPE_2__ flags; int /*<<< orphan*/  output_format; } ;
struct diff_filepair {TYPE_8__* one; } ;
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct blame_scoreboard {scalar_t__ copy_score; int /*<<< orphan*/  num_read_blob; TYPE_3__* revs; int /*<<< orphan*/  repo; } ;
struct blame_origin {struct blame_entry* suspects; int /*<<< orphan*/  mode; int /*<<< orphan*/  blob_oid; int /*<<< orphan*/  path; struct commit* commit; } ;
struct blame_list {struct blame_entry* ent; struct blame_entry* split; } ;
struct blame_entry {struct blame_entry* next; scalar_t__ suspect; } ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ mmfile_t ;
struct TYPE_14__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct TYPE_13__ {int nr; struct diff_filepair** queue; } ;
struct TYPE_11__ {int /*<<< orphan*/  diffopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_VALID (TYPE_8__*) ; 
 int /*<<< orphan*/  DIFF_FORMAT_NO_OUTPUT ; 
 int PICKAXE_BLAME_COPY_HARDER ; 
 int PICKAXE_BLAME_COPY_HARDEST ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ blame_entry_score (struct blame_scoreboard*,struct blame_entry*) ; 
 int /*<<< orphan*/  blame_origin_decref (struct blame_origin*) ; 
 int /*<<< orphan*/  clear_pathspec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_split_if_better (struct blame_scoreboard*,struct blame_entry*,struct blame_entry*) ; 
 int /*<<< orphan*/  decref_split (struct blame_entry*) ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 TYPE_7__ diff_queued_diff ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  do_diff_cache (int /*<<< orphan*/ ,struct diff_options*) ; 
 int /*<<< orphan*/  fill_origin_blob (int /*<<< orphan*/ *,struct blame_origin*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct blame_entry** filter_small (struct blame_scoreboard*,struct blame_entry**,struct blame_entry**,scalar_t__) ; 
 int /*<<< orphan*/  find_copy_in_blob (struct blame_scoreboard*,struct blame_entry*,struct blame_origin*,struct blame_entry*,TYPE_4__*) ; 
 int /*<<< orphan*/  free (struct blame_list*) ; 
 int /*<<< orphan*/  get_commit_tree_oid (struct commit*) ; 
 struct blame_origin* get_origin (struct commit*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_diff_setup (int /*<<< orphan*/ ,struct diff_options*) ; 
 struct blame_entry* reverse_blame (struct blame_entry*,int /*<<< orphan*/ *) ; 
 struct blame_list* setup_blame_list (struct blame_entry*,int*) ; 
 int /*<<< orphan*/  split_blame (struct blame_entry***,struct blame_entry***,struct blame_entry*,struct blame_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_copy_in_parent(struct blame_scoreboard *sb,
				struct blame_entry ***blamed,
				struct blame_entry **toosmall,
				struct blame_origin *target,
				struct commit *parent,
				struct blame_origin *porigin,
				int opt)
{
	struct diff_options diff_opts;
	int i, j;
	struct blame_list *blame_list;
	int num_ents;
	struct blame_entry *unblamed = target->suspects;
	struct blame_entry *leftover = NULL;

	if (!unblamed)
		return; /* nothing remains for this target */

	repo_diff_setup(sb->repo, &diff_opts);
	diff_opts.flags.recursive = 1;
	diff_opts.output_format = DIFF_FORMAT_NO_OUTPUT;

	diff_setup_done(&diff_opts);

	/* Try "find copies harder" on new path if requested;
	 * we do not want to use diffcore_rename() actually to
	 * match things up; find_copies_harder is set only to
	 * force diff_tree_oid() to feed all filepairs to diff_queue,
	 * and this code needs to be after diff_setup_done(), which
	 * usually makes find-copies-harder imply copy detection.
	 */
	if ((opt & PICKAXE_BLAME_COPY_HARDEST)
	    || ((opt & PICKAXE_BLAME_COPY_HARDER)
		&& (!porigin || strcmp(target->path, porigin->path))))
		diff_opts.flags.find_copies_harder = 1;

	if (is_null_oid(&target->commit->object.oid))
		do_diff_cache(get_commit_tree_oid(parent), &diff_opts);
	else
		diff_tree_oid(get_commit_tree_oid(parent),
			      get_commit_tree_oid(target->commit),
			      "", &diff_opts);

	if (!diff_opts.flags.find_copies_harder)
		diffcore_std(&diff_opts);

	do {
		struct blame_entry **unblamedtail = &unblamed;
		blame_list = setup_blame_list(unblamed, &num_ents);

		for (i = 0; i < diff_queued_diff.nr; i++) {
			struct diff_filepair *p = diff_queued_diff.queue[i];
			struct blame_origin *norigin;
			mmfile_t file_p;
			struct blame_entry potential[3];

			if (!DIFF_FILE_VALID(p->one))
				continue; /* does not exist in parent */
			if (S_ISGITLINK(p->one->mode))
				continue; /* ignore git links */
			if (porigin && !strcmp(p->one->path, porigin->path))
				/* find_move already dealt with this path */
				continue;

			norigin = get_origin(parent, p->one->path);
			oidcpy(&norigin->blob_oid, &p->one->oid);
			norigin->mode = p->one->mode;
			fill_origin_blob(&sb->revs->diffopt, norigin, &file_p,
					 &sb->num_read_blob, 0);
			if (!file_p.ptr)
				continue;

			for (j = 0; j < num_ents; j++) {
				find_copy_in_blob(sb, blame_list[j].ent,
						  norigin, potential, &file_p);
				copy_split_if_better(sb, blame_list[j].split,
						     potential);
				decref_split(potential);
			}
			blame_origin_decref(norigin);
		}

		for (j = 0; j < num_ents; j++) {
			struct blame_entry *split = blame_list[j].split;
			if (split[1].suspect &&
			    sb->copy_score < blame_entry_score(sb, &split[1])) {
				split_blame(blamed, &unblamedtail, split,
					    blame_list[j].ent);
			} else {
				blame_list[j].ent->next = leftover;
				leftover = blame_list[j].ent;
			}
			decref_split(split);
		}
		free(blame_list);
		*unblamedtail = NULL;
		toosmall = filter_small(sb, toosmall, &unblamed, sb->copy_score);
	} while (unblamed);
	target->suspects = reverse_blame(leftover, NULL);
	diff_flush(&diff_opts);
	clear_pathspec(&diff_opts.pathspec);
}