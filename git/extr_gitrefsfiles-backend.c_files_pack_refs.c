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
struct ref_to_prune {struct ref_to_prune* next; int /*<<< orphan*/  oid; } ;
struct ref_store {int dummy; } ;
struct ref_iterator {int /*<<< orphan*/  oid; int /*<<< orphan*/  refname; int /*<<< orphan*/  flags; } ;
struct files_ref_store {int /*<<< orphan*/  packed_ref_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct ref_to_prune*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ITER_DONE ; 
 int ITER_OK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 unsigned int PACK_REFS_PRUNE ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int REF_STORE_ODB ; 
 int REF_STORE_WRITE ; 
 struct strbuf STRBUF_INIT ; 
 struct ref_iterator* cache_ref_iterator_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int,char*) ; 
 int /*<<< orphan*/  get_loose_ref_cache (struct files_ref_store*) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_refs_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  packed_refs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_refs (struct files_ref_store*,struct ref_to_prune**) ; 
 int ref_iterator_advance (struct ref_iterator*) ; 
 struct ref_transaction* ref_store_transaction_begin (int /*<<< orphan*/ ,struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  should_pack_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int files_pack_refs(struct ref_store *ref_store, unsigned int flags)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE | REF_STORE_ODB,
			       "pack_refs");
	struct ref_iterator *iter;
	int ok;
	struct ref_to_prune *refs_to_prune = NULL;
	struct strbuf err = STRBUF_INIT;
	struct ref_transaction *transaction;

	transaction = ref_store_transaction_begin(refs->packed_ref_store, &err);
	if (!transaction)
		return -1;

	packed_refs_lock(refs->packed_ref_store, LOCK_DIE_ON_ERROR, &err);

	iter = cache_ref_iterator_begin(get_loose_ref_cache(refs), NULL, 0);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		/*
		 * If the loose reference can be packed, add an entry
		 * in the packed ref cache. If the reference should be
		 * pruned, also add it to refs_to_prune.
		 */
		if (!should_pack_ref(iter->refname, iter->oid, iter->flags,
				     flags))
			continue;

		/*
		 * Add a reference creation for this reference to the
		 * packed-refs transaction:
		 */
		if (ref_transaction_update(transaction, iter->refname,
					   iter->oid, NULL,
					   REF_NO_DEREF, NULL, &err))
			die("failure preparing to create packed reference %s: %s",
			    iter->refname, err.buf);

		/* Schedule the loose reference for pruning if requested. */
		if ((flags & PACK_REFS_PRUNE)) {
			struct ref_to_prune *n;
			FLEX_ALLOC_STR(n, name, iter->refname);
			oidcpy(&n->oid, iter->oid);
			n->next = refs_to_prune;
			refs_to_prune = n;
		}
	}
	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (ref_transaction_commit(transaction, &err))
		die("unable to write new packed-refs: %s", err.buf);

	ref_transaction_free(transaction);

	packed_refs_unlock(refs->packed_ref_store);

	prune_refs(refs, &refs_to_prune);
	strbuf_release(&err);
	return 0;
}