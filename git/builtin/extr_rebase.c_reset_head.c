#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unpack_tree_opts ;
struct unpack_trees_options {int head_idx; int update; int merge; int reset; int /*<<< orphan*/  fn; int /*<<< orphan*/  dst_index; int /*<<< orphan*/  src_index; } ;
struct tree_desc {scalar_t__ buffer; int /*<<< orphan*/ * member_0; } ;
struct tree {int dummy; } ;
struct strbuf {size_t len; char* buf; } ;
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  GIT_REFLOG_ACTION_ENVIRONMENT ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  LOCK_REPORT_ON_ERROR ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 unsigned int RESET_HEAD_DETACH ; 
 unsigned int RESET_HEAD_HARD ; 
 unsigned int RESET_HEAD_REFS_ONLY ; 
 unsigned int RESET_HEAD_RUN_POST_CHECKOUT_HOOK ; 
 unsigned int RESET_ORIG_HEAD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int create_symref (char*,char const*,char const*) ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,struct object_id*,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fill_tree_descriptor (TYPE_1__*,struct tree_desc*,struct object_id*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 scalar_t__ hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 struct object_id null_oid ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oneway_merge ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 int /*<<< orphan*/  prime_cache_tree (TYPE_1__*,int /*<<< orphan*/ ,struct tree*) ; 
 scalar_t__ repo_read_index_unmerged (TYPE_1__*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  run_hook_le (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_unpack_trees_porcelain (struct unpack_trees_options*,char const*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 TYPE_1__* the_repository ; 
 int /*<<< orphan*/  twoway_merge ; 
 scalar_t__ unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 
 int update_ref (char const*,char const*,struct object_id*,struct object_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_head(struct object_id *oid, const char *action,
		      const char *switch_to_branch, unsigned flags,
		      const char *reflog_orig_head, const char *reflog_head)
{
	unsigned detach_head = flags & RESET_HEAD_DETACH;
	unsigned reset_hard = flags & RESET_HEAD_HARD;
	unsigned run_hook = flags & RESET_HEAD_RUN_POST_CHECKOUT_HOOK;
	unsigned refs_only = flags & RESET_HEAD_REFS_ONLY;
	unsigned update_orig_head = flags & RESET_ORIG_HEAD;
	struct object_id head_oid;
	struct tree_desc desc[2] = { { NULL }, { NULL } };
	struct lock_file lock = LOCK_INIT;
	struct unpack_trees_options unpack_tree_opts;
	struct tree *tree;
	const char *reflog_action;
	struct strbuf msg = STRBUF_INIT;
	size_t prefix_len;
	struct object_id *orig = NULL, oid_orig,
		*old_orig = NULL, oid_old_orig;
	int ret = 0, nr = 0;

	if (switch_to_branch && !starts_with(switch_to_branch, "refs/"))
		BUG("Not a fully qualified branch: '%s'", switch_to_branch);

	if (!refs_only && hold_locked_index(&lock, LOCK_REPORT_ON_ERROR) < 0) {
		ret = -1;
		goto leave_reset_head;
	}

	if ((!oid || !reset_hard) && get_oid("HEAD", &head_oid)) {
		ret = error(_("could not determine HEAD revision"));
		goto leave_reset_head;
	}

	if (!oid)
		oid = &head_oid;

	if (refs_only)
		goto reset_head_refs;

	memset(&unpack_tree_opts, 0, sizeof(unpack_tree_opts));
	setup_unpack_trees_porcelain(&unpack_tree_opts, action);
	unpack_tree_opts.head_idx = 1;
	unpack_tree_opts.src_index = the_repository->index;
	unpack_tree_opts.dst_index = the_repository->index;
	unpack_tree_opts.fn = reset_hard ? oneway_merge : twoway_merge;
	unpack_tree_opts.update = 1;
	unpack_tree_opts.merge = 1;
	if (!detach_head)
		unpack_tree_opts.reset = 1;

	if (repo_read_index_unmerged(the_repository) < 0) {
		ret = error(_("could not read index"));
		goto leave_reset_head;
	}

	if (!reset_hard && !fill_tree_descriptor(the_repository, &desc[nr++], &head_oid)) {
		ret = error(_("failed to find tree of %s"),
			    oid_to_hex(&head_oid));
		goto leave_reset_head;
	}

	if (!fill_tree_descriptor(the_repository, &desc[nr++], oid)) {
		ret = error(_("failed to find tree of %s"), oid_to_hex(oid));
		goto leave_reset_head;
	}

	if (unpack_trees(nr, desc, &unpack_tree_opts)) {
		ret = -1;
		goto leave_reset_head;
	}

	tree = parse_tree_indirect(oid);
	prime_cache_tree(the_repository, the_repository->index, tree);

	if (write_locked_index(the_repository->index, &lock, COMMIT_LOCK) < 0) {
		ret = error(_("could not write index"));
		goto leave_reset_head;
	}

reset_head_refs:
	reflog_action = getenv(GIT_REFLOG_ACTION_ENVIRONMENT);
	strbuf_addf(&msg, "%s: ", reflog_action ? reflog_action : "rebase");
	prefix_len = msg.len;

	if (update_orig_head) {
		if (!get_oid("ORIG_HEAD", &oid_old_orig))
			old_orig = &oid_old_orig;
		if (!get_oid("HEAD", &oid_orig)) {
			orig = &oid_orig;
			if (!reflog_orig_head) {
				strbuf_addstr(&msg, "updating ORIG_HEAD");
				reflog_orig_head = msg.buf;
			}
			update_ref(reflog_orig_head, "ORIG_HEAD", orig,
				   old_orig, 0, UPDATE_REFS_MSG_ON_ERR);
		} else if (old_orig)
			delete_ref(NULL, "ORIG_HEAD", old_orig, 0);
	}

	if (!reflog_head) {
		strbuf_setlen(&msg, prefix_len);
		strbuf_addstr(&msg, "updating HEAD");
		reflog_head = msg.buf;
	}
	if (!switch_to_branch)
		ret = update_ref(reflog_head, "HEAD", oid, orig,
				 detach_head ? REF_NO_DEREF : 0,
				 UPDATE_REFS_MSG_ON_ERR);
	else {
		ret = update_ref(reflog_head, switch_to_branch, oid,
				 NULL, 0, UPDATE_REFS_MSG_ON_ERR);
		if (!ret)
			ret = create_symref("HEAD", switch_to_branch,
					    reflog_head);
	}
	if (run_hook)
		run_hook_le(NULL, "post-checkout",
			    oid_to_hex(orig ? orig : &null_oid),
			    oid_to_hex(oid), "1", NULL);

leave_reset_head:
	strbuf_release(&msg);
	rollback_lock_file(&lock);
	while (nr)
		free((void *)desc[--nr].buffer);
	return ret;
}