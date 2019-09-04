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
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ REF_TYPE_PSEUDOREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int delete_pseudoref (char const*,struct object_id const*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 struct ref_store* get_main_ref_store (int /*<<< orphan*/ ) ; 
 struct ref_transaction* ref_store_transaction_begin (struct ref_store*,struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 scalar_t__ ref_transaction_delete (struct ref_transaction*,char const*,struct object_id const*,unsigned int,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_type (char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

int refs_delete_ref(struct ref_store *refs, const char *msg,
		    const char *refname,
		    const struct object_id *old_oid,
		    unsigned int flags)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (ref_type(refname) == REF_TYPE_PSEUDOREF) {
		assert(refs == get_main_ref_store(the_repository));
		return delete_pseudoref(refname, old_oid);
	}

	transaction = ref_store_transaction_begin(refs, &err);
	if (!transaction ||
	    ref_transaction_delete(transaction, refname, old_oid,
				   flags, msg, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		error("%s", err.buf);
		ref_transaction_free(transaction);
		strbuf_release(&err);
		return 1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	return 0;
}