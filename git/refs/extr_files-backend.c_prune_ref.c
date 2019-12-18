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
struct ref_to_prune {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
struct files_ref_store {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int REF_HAVE_NEW ; 
 int REF_HAVE_OLD ; 
 int REF_IS_PRUNING ; 
 int REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 struct ref_transaction* ref_store_transaction_begin (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_add_update (struct ref_transaction*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void prune_ref(struct files_ref_store *refs, struct ref_to_prune *r)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;
	int ret = -1;

	if (check_refname_format(r->name, 0))
		return;

	transaction = ref_store_transaction_begin(&refs->base, &err);
	if (!transaction)
		goto cleanup;
	ref_transaction_add_update(
			transaction, r->name,
			REF_NO_DEREF | REF_HAVE_NEW | REF_HAVE_OLD | REF_IS_PRUNING,
			&null_oid, &r->oid, NULL);
	if (ref_transaction_commit(transaction, &err))
		goto cleanup;

	ret = 0;

cleanup:
	if (ret)
		error("%s", err.buf);
	strbuf_release(&err);
	ref_transaction_free(transaction);
	return;
}