#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
struct commit_list {struct commit* item; } ;
struct TYPE_20__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_16__ object; TYPE_2__* parents; } ;
struct TYPE_21__ {int /*<<< orphan*/  compare; } ;
struct blame_scoreboard {int /*<<< orphan*/  num_read_blob; scalar_t__ final_buf; int /*<<< orphan*/  final_buf_size; int /*<<< orphan*/  repo; TYPE_5__* revs; TYPE_6__* final; scalar_t__ reverse; scalar_t__ contents_from; TYPE_1__ commits; } ;
struct TYPE_23__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct blame_origin {int /*<<< orphan*/  blob_oid; int /*<<< orphan*/  mode; TYPE_3__ file; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_18__ {int /*<<< orphan*/  oid; } ;
struct TYPE_26__ {TYPE_14__ object; } ;
struct TYPE_24__ {scalar_t__ allow_textconv; } ;
struct TYPE_17__ {TYPE_4__ flags; } ;
struct TYPE_19__ {char* name; } ;
struct TYPE_25__ {TYPE_12__ diffopt; TYPE_15__ children; scalar_t__ first_parent_only; } ;
struct TYPE_22__ {struct commit* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_decoration (TYPE_15__*,TYPE_16__*,struct commit_list*) ; 
 int /*<<< orphan*/  add_pending_object (TYPE_5__*,TYPE_14__*,char*) ; 
 int /*<<< orphan*/  blame_suspects ; 
 int /*<<< orphan*/  compare_commits_by_commit_date ; 
 int /*<<< orphan*/  compare_commits_by_reverse_commit_date ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 TYPE_6__* fake_working_tree_commit (int /*<<< orphan*/ ,TYPE_12__*,char const*,scalar_t__) ; 
 scalar_t__ fill_blob_sha1_and_mode (int /*<<< orphan*/ ,struct blame_origin*) ; 
 void* find_single_final (TYPE_5__*,char const**) ; 
 TYPE_6__* find_single_initial (TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct blame_origin* get_blame_suspects (TYPE_6__*) ; 
 struct blame_origin* get_origin (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/  init_blame_suspects (int /*<<< orphan*/ *) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 char const* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lines (struct blame_scoreboard*) ; 
 scalar_t__ prepare_revision_walk (TYPE_5__*) ; 
 scalar_t__ read_object_file (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_work_tree () ; 
 scalar_t__ textconv_object (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ *) ; 
 struct commit_list* xcalloc (int,int) ; 
 scalar_t__ xmemdupz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void setup_scoreboard(struct blame_scoreboard *sb,
		      const char *path,
		      struct blame_origin **orig)
{
	const char *final_commit_name = NULL;
	struct blame_origin *o;
	struct commit *final_commit = NULL;
	enum object_type type;

	init_blame_suspects(&blame_suspects);

	if (sb->reverse && sb->contents_from)
		die(_("--contents and --reverse do not blend well."));

	if (!sb->repo)
		BUG("repo is NULL");

	if (!sb->reverse) {
		sb->final = find_single_final(sb->revs, &final_commit_name);
		sb->commits.compare = compare_commits_by_commit_date;
	} else {
		sb->final = find_single_initial(sb->revs, &final_commit_name);
		sb->commits.compare = compare_commits_by_reverse_commit_date;
	}

	if (sb->final && sb->contents_from)
		die(_("cannot use --contents with final commit object name"));

	if (sb->reverse && sb->revs->first_parent_only)
		sb->revs->children.name = NULL;

	if (!sb->final) {
		/*
		 * "--not A B -- path" without anything positive;
		 * do not default to HEAD, but use the working tree
		 * or "--contents".
		 */
		setup_work_tree();
		sb->final = fake_working_tree_commit(sb->repo,
						     &sb->revs->diffopt,
						     path, sb->contents_from);
		add_pending_object(sb->revs, &(sb->final->object), ":");
	}

	if (sb->reverse && sb->revs->first_parent_only) {
		final_commit = find_single_final(sb->revs, NULL);
		if (!final_commit)
			die(_("--reverse and --first-parent together require specified latest commit"));
	}

	/*
	 * If we have bottom, this will mark the ancestors of the
	 * bottom commits we would reach while traversing as
	 * uninteresting.
	 */
	if (prepare_revision_walk(sb->revs))
		die(_("revision walk setup failed"));

	if (sb->reverse && sb->revs->first_parent_only) {
		struct commit *c = final_commit;

		sb->revs->children.name = "children";
		while (c->parents &&
		       !oideq(&c->object.oid, &sb->final->object.oid)) {
			struct commit_list *l = xcalloc(1, sizeof(*l));

			l->item = c;
			if (add_decoration(&sb->revs->children,
					   &c->parents->item->object, l))
				BUG("not unique item in first-parent chain");
			c = c->parents->item;
		}

		if (!oideq(&c->object.oid, &sb->final->object.oid))
			die(_("--reverse --first-parent together require range along first-parent chain"));
	}

	if (is_null_oid(&sb->final->object.oid)) {
		o = get_blame_suspects(sb->final);
		sb->final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb->final_buf_size = o->file.size;
	}
	else {
		o = get_origin(sb->final, path);
		if (fill_blob_sha1_and_mode(sb->repo, o))
			die(_("no such path %s in %s"), path, final_commit_name);

		if (sb->revs->diffopt.flags.allow_textconv &&
		    textconv_object(sb->repo, path, o->mode, &o->blob_oid, 1, (char **) &sb->final_buf,
				    &sb->final_buf_size))
			;
		else
			sb->final_buf = read_object_file(&o->blob_oid, &type,
							 &sb->final_buf_size);

		if (!sb->final_buf)
			die(_("cannot read blob %s for path %s"),
			    oid_to_hex(&o->blob_oid),
			    path);
	}
	sb->num_read_blob++;
	prepare_lines(sb);

	if (orig)
		*orig = o;

	free((char *)final_commit_name);
}