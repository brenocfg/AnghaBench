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
typedef  int /*<<< orphan*/  unpack_tree_opts ;
struct unpack_trees_options {int head_idx; int merge; int update; int /*<<< orphan*/  fn; int /*<<< orphan*/  dst_index; int /*<<< orphan*/  src_index; } ;
struct tree_desc {scalar_t__ buffer; } ;
struct tree {int dummy; } ;
struct strbuf {scalar_t__ buf; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct object_id {int dummy; } ;
struct replay_opts {int have_squash_onto; struct object_id squash_onto; } ;
struct lock_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  empty_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  LOCK_REPORT_ON_ERROR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* action_name (struct replay_opts*) ; 
 scalar_t__ commit_tree (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int error_resolve_conflict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_tree_descriptor (struct repository*,struct tree_desc*,struct object_id*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ get_oid (scalar_t__,struct object_id*) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  oneway_merge ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 int /*<<< orphan*/  prime_cache_tree (struct repository*,int /*<<< orphan*/ ,struct tree*) ; 
 int /*<<< orphan*/  rebase_path_squash_onto () ; 
 int /*<<< orphan*/  reflog_message (struct replay_opts*,char*,char*,int,char const*) ; 
 scalar_t__ repo_hold_locked_index (struct repository*,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index_unmerged (struct repository*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  setup_unpack_trees_porcelain (struct unpack_trees_options*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 TYPE_1__* the_hash_algo ; 
 scalar_t__ unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 
 int update_ref (int /*<<< orphan*/ ,char*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_message (char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_reset(struct repository *r,
		    const char *name, int len,
		    struct replay_opts *opts)
{
	struct strbuf ref_name = STRBUF_INIT;
	struct object_id oid;
	struct lock_file lock = LOCK_INIT;
	struct tree_desc desc;
	struct tree *tree;
	struct unpack_trees_options unpack_tree_opts;
	int ret = 0;

	if (repo_hold_locked_index(r, &lock, LOCK_REPORT_ON_ERROR) < 0)
		return -1;

	if (len == 10 && !strncmp("[new root]", name, len)) {
		if (!opts->have_squash_onto) {
			const char *hex;
			if (commit_tree("", 0, the_hash_algo->empty_tree,
					NULL, &opts->squash_onto,
					NULL, NULL))
				return error(_("writing fake root commit"));
			opts->have_squash_onto = 1;
			hex = oid_to_hex(&opts->squash_onto);
			if (write_message(hex, strlen(hex),
					  rebase_path_squash_onto(), 0))
				return error(_("writing squash-onto"));
		}
		oidcpy(&oid, &opts->squash_onto);
	} else {
		int i;

		/* Determine the length of the label */
		for (i = 0; i < len; i++)
			if (isspace(name[i]))
				break;
		len = i;

		strbuf_addf(&ref_name, "refs/rewritten/%.*s", len, name);
		if (get_oid(ref_name.buf, &oid) &&
		    get_oid(ref_name.buf + strlen("refs/rewritten/"), &oid)) {
			error(_("could not read '%s'"), ref_name.buf);
			rollback_lock_file(&lock);
			strbuf_release(&ref_name);
			return -1;
		}
	}

	memset(&unpack_tree_opts, 0, sizeof(unpack_tree_opts));
	setup_unpack_trees_porcelain(&unpack_tree_opts, "reset");
	unpack_tree_opts.head_idx = 1;
	unpack_tree_opts.src_index = r->index;
	unpack_tree_opts.dst_index = r->index;
	unpack_tree_opts.fn = oneway_merge;
	unpack_tree_opts.merge = 1;
	unpack_tree_opts.update = 1;

	if (repo_read_index_unmerged(r)) {
		rollback_lock_file(&lock);
		strbuf_release(&ref_name);
		return error_resolve_conflict(_(action_name(opts)));
	}

	if (!fill_tree_descriptor(r, &desc, &oid)) {
		error(_("failed to find tree of %s"), oid_to_hex(&oid));
		rollback_lock_file(&lock);
		free((void *)desc.buffer);
		strbuf_release(&ref_name);
		return -1;
	}

	if (unpack_trees(1, &desc, &unpack_tree_opts)) {
		rollback_lock_file(&lock);
		free((void *)desc.buffer);
		strbuf_release(&ref_name);
		return -1;
	}

	tree = parse_tree_indirect(&oid);
	prime_cache_tree(r, r->index, tree);

	if (write_locked_index(r->index, &lock, COMMIT_LOCK) < 0)
		ret = error(_("could not write index"));
	free((void *)desc.buffer);

	if (!ret)
		ret = update_ref(reflog_message(opts, "reset", "'%.*s'",
						len, name), "HEAD", &oid,
				 NULL, 0, UPDATE_REFS_MSG_ON_ERR);

	strbuf_release(&ref_name);
	return ret;
}