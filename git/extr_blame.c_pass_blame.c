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
struct rev_info {int dummy; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct blame_scoreboard {int no_whole_file_rename; struct repository* repo; int /*<<< orphan*/  reverse; int /*<<< orphan*/  copy_score; int /*<<< orphan*/  move_score; int /*<<< orphan*/  ignore_list; int /*<<< orphan*/  num_commits; struct rev_info* revs; } ;
struct blame_origin {struct blame_entry* suspects; struct blame_origin* previous; int /*<<< orphan*/  blob_oid; struct commit* commit; } ;
struct blame_entry {struct blame_entry* next; } ;
typedef  int /*<<< orphan*/  sg_buf ;

/* Variables and functions */
 int ARRAY_SIZE (struct blame_origin**) ; 
 int MAXSG ; 
 int PICKAXE_BLAME_COPY ; 
 int PICKAXE_BLAME_MOVE ; 
 struct blame_entry* blame_merge (struct blame_entry*,struct blame_entry*) ; 
 int /*<<< orphan*/  blame_origin_decref (struct blame_origin*) ; 
 int /*<<< orphan*/  blame_origin_incref (struct blame_origin*) ; 
 int /*<<< orphan*/  distribute_blame (struct blame_scoreboard*,struct blame_entry*) ; 
 int /*<<< orphan*/  drop_origin_blob (struct blame_origin*) ; 
 int /*<<< orphan*/  filter_small (struct blame_scoreboard*,struct blame_entry**,struct blame_entry**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_copy_in_parent (struct blame_scoreboard*,struct blame_entry***,struct blame_entry**,struct blame_origin*,struct commit*,struct blame_origin*,int) ; 
 int /*<<< orphan*/  find_move_in_parent (struct blame_scoreboard*,struct blame_entry***,struct blame_entry**,struct blame_origin*,struct blame_origin*) ; 
 struct blame_origin* find_origin (struct repository*,struct commit*,struct blame_origin*) ; 
 struct blame_origin* find_rename (struct repository*,struct commit*,struct blame_origin*) ; 
 struct commit_list* first_scapegoat (struct rev_info*,struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct blame_origin**) ; 
 int /*<<< orphan*/  memset (struct blame_origin**,int /*<<< orphan*/ ,int) ; 
 int num_scapegoats (struct rev_info*,struct commit*,int /*<<< orphan*/ ) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oidset_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  pass_blame_to_parent (struct blame_scoreboard*,struct blame_origin*,struct blame_origin*,int) ; 
 int /*<<< orphan*/  pass_whole_blame (struct blame_scoreboard*,struct blame_origin*,struct blame_origin*) ; 
 struct blame_origin** xcalloc (int,int) ; 

__attribute__((used)) static void pass_blame(struct blame_scoreboard *sb, struct blame_origin *origin, int opt)
{
	struct rev_info *revs = sb->revs;
	int i, pass, num_sg;
	struct commit *commit = origin->commit;
	struct commit_list *sg;
	struct blame_origin *sg_buf[MAXSG];
	struct blame_origin *porigin, **sg_origin = sg_buf;
	struct blame_entry *toosmall = NULL;
	struct blame_entry *blames, **blametail = &blames;

	num_sg = num_scapegoats(revs, commit, sb->reverse);
	if (!num_sg)
		goto finish;
	else if (num_sg < ARRAY_SIZE(sg_buf))
		memset(sg_buf, 0, sizeof(sg_buf));
	else
		sg_origin = xcalloc(num_sg, sizeof(*sg_origin));

	/*
	 * The first pass looks for unrenamed path to optimize for
	 * common cases, then we look for renames in the second pass.
	 */
	for (pass = 0; pass < 2 - sb->no_whole_file_rename; pass++) {
		struct blame_origin *(*find)(struct repository *, struct commit *, struct blame_origin *);
		find = pass ? find_rename : find_origin;

		for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct commit *p = sg->item;
			int j, same;

			if (sg_origin[i])
				continue;
			if (parse_commit(p))
				continue;
			porigin = find(sb->repo, p, origin);
			if (!porigin)
				continue;
			if (oideq(&porigin->blob_oid, &origin->blob_oid)) {
				pass_whole_blame(sb, origin, porigin);
				blame_origin_decref(porigin);
				goto finish;
			}
			for (j = same = 0; j < i; j++)
				if (sg_origin[j] &&
				    oideq(&sg_origin[j]->blob_oid, &porigin->blob_oid)) {
					same = 1;
					break;
				}
			if (!same)
				sg_origin[i] = porigin;
			else
				blame_origin_decref(porigin);
		}
	}

	sb->num_commits++;
	for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
	     i < num_sg && sg;
	     sg = sg->next, i++) {
		struct blame_origin *porigin = sg_origin[i];
		if (!porigin)
			continue;
		if (!origin->previous) {
			blame_origin_incref(porigin);
			origin->previous = porigin;
		}
		pass_blame_to_parent(sb, origin, porigin, 0);
		if (!origin->suspects)
			goto finish;
	}

	/*
	 * Pass remaining suspects for ignored commits to their parents.
	 */
	if (oidset_contains(&sb->ignore_list, &commit->object.oid)) {
		for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct blame_origin *porigin = sg_origin[i];

			if (!porigin)
				continue;
			pass_blame_to_parent(sb, origin, porigin, 1);
			/*
			 * Preemptively drop porigin so we can refresh the
			 * fingerprints if we use the parent again, which can
			 * occur if you ignore back-to-back commits.
			 */
			drop_origin_blob(porigin);
			if (!origin->suspects)
				goto finish;
		}
	}

	/*
	 * Optionally find moves in parents' files.
	 */
	if (opt & PICKAXE_BLAME_MOVE) {
		filter_small(sb, &toosmall, &origin->suspects, sb->move_score);
		if (origin->suspects) {
			for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
			     i < num_sg && sg;
			     sg = sg->next, i++) {
				struct blame_origin *porigin = sg_origin[i];
				if (!porigin)
					continue;
				find_move_in_parent(sb, &blametail, &toosmall, origin, porigin);
				if (!origin->suspects)
					break;
			}
		}
	}

	/*
	 * Optionally find copies from parents' files.
	 */
	if (opt & PICKAXE_BLAME_COPY) {
		if (sb->copy_score > sb->move_score)
			filter_small(sb, &toosmall, &origin->suspects, sb->copy_score);
		else if (sb->copy_score < sb->move_score) {
			origin->suspects = blame_merge(origin->suspects, toosmall);
			toosmall = NULL;
			filter_small(sb, &toosmall, &origin->suspects, sb->copy_score);
		}
		if (!origin->suspects)
			goto finish;

		for (i = 0, sg = first_scapegoat(revs, commit, sb->reverse);
		     i < num_sg && sg;
		     sg = sg->next, i++) {
			struct blame_origin *porigin = sg_origin[i];
			find_copy_in_parent(sb, &blametail, &toosmall,
					    origin, sg->item, porigin, opt);
			if (!origin->suspects)
				goto finish;
		}
	}

finish:
	*blametail = NULL;
	distribute_blame(sb, blames);
	/*
	 * prepend toosmall to origin->suspects
	 *
	 * There is no point in sorting: this ends up on a big
	 * unsorted list in the caller anyway.
	 */
	if (toosmall) {
		struct blame_entry **tail = &toosmall;
		while (*tail)
			tail = &(*tail)->next;
		*tail = origin->suspects;
		origin->suspects = toosmall;
	}
	for (i = 0; i < num_sg; i++) {
		if (sg_origin[i]) {
			if (!sg_origin[i]->suspects)
				drop_origin_blob(sg_origin[i]);
			blame_origin_decref(sg_origin[i]);
		}
	}
	drop_origin_blob(origin);
	if (sg_buf != sg_origin)
		free(sg_origin);
}