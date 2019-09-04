#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct replay_opts {int dummy; } ;
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* action_name (struct replay_opts*) ; 
 scalar_t__ checkout_fast_forward (struct repository*,struct object_id const*,struct object_id const*,int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_rebase_i (struct replay_opts*) ; 
 struct object_id const null_oid ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,char*,struct object_id const*,struct object_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_abort_safety_file () ; 

__attribute__((used)) static int fast_forward_to(struct repository *r,
			   const struct object_id *to,
			   const struct object_id *from,
			   int unborn,
			   struct replay_opts *opts)
{
	struct ref_transaction *transaction;
	struct strbuf sb = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;

	repo_read_index(r);
	if (checkout_fast_forward(r, from, to, 1))
		return -1; /* the callee should have complained already */

	strbuf_addf(&sb, _("%s: fast-forward"), _(action_name(opts)));

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, "HEAD",
				   to, unborn && !is_rebase_i(opts) ?
				   &null_oid : from,
				   0, sb.buf, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&sb);
		strbuf_release(&err);
		return -1;
	}

	strbuf_release(&sb);
	strbuf_release(&err);
	ref_transaction_free(transaction);
	update_abort_safety_file();
	return 0;
}