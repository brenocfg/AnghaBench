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
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
struct branch {struct object_id oid; int /*<<< orphan*/  name; scalar_t__ delete; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_update ; 
 int /*<<< orphan*/  in_merge_bases (struct commit*,struct commit*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 scalar_t__ read_ref (int /*<<< orphan*/ ,struct object_id*) ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,int /*<<< orphan*/ ,struct object_id*,struct object_id*,int /*<<< orphan*/ ,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_branch(struct branch *b)
{
	static const char *msg = "fast-import";
	struct ref_transaction *transaction;
	struct object_id old_oid;
	struct strbuf err = STRBUF_INIT;

	if (is_null_oid(&b->oid)) {
		if (b->delete)
			delete_ref(NULL, b->name, NULL, 0);
		return 0;
	}
	if (read_ref(b->name, &old_oid))
		oidclr(&old_oid);
	if (!force_update && !is_null_oid(&old_oid)) {
		struct commit *old_cmit, *new_cmit;

		old_cmit = lookup_commit_reference_gently(the_repository,
							  &old_oid, 0);
		new_cmit = lookup_commit_reference_gently(the_repository,
							  &b->oid, 0);
		if (!old_cmit || !new_cmit)
			return error("Branch %s is missing commits.", b->name);

		if (!in_merge_bases(old_cmit, new_cmit)) {
			warning("Not updating %s"
				" (new tip %s does not contain %s)",
				b->name, oid_to_hex(&b->oid),
				oid_to_hex(&old_oid));
			return -1;
		}
	}
	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, b->name, &b->oid, &old_oid,
				   0, msg, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	return 0;
}