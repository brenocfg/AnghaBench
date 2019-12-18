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
struct string_list_item {struct ref_update* util; } ;
struct string_list {int dummy; } ;
struct strbuf {int dummy; } ;
struct ref_update {int flags; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  refname; } ;
struct ref_transaction {size_t nr; int /*<<< orphan*/  state; struct ref_update** updates; struct files_transaction_backend_data* backend_data; } ;
struct ref_store {int dummy; } ;
struct files_transaction_backend_data {int packed_refs_locked; struct ref_transaction* packed_transaction; } ;
struct files_ref_store {int /*<<< orphan*/  packed_ref_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 int REF_DELETING ; 
 int REF_HAVE_NEW ; 
 int REF_ISSYMREF ; 
 int REF_IS_PRUNING ; 
 int REF_LOG_ONLY ; 
 int REF_NO_DEREF ; 
 int /*<<< orphan*/  REF_STORE_WRITE ; 
 int /*<<< orphan*/  REF_TRANSACTION_PREPARED ; 
 int /*<<< orphan*/  RESOLVE_REF_NO_RECURSE ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int TRANSACTION_GENERIC_ERROR ; 
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_transaction_cleanup (struct files_ref_store*,struct ref_transaction*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_packed_transaction_needed (int /*<<< orphan*/ ,struct ref_transaction*) ; 
 int lock_ref_for_update (struct files_ref_store*,struct ref_update*,struct ref_transaction*,char*,struct string_list*,struct strbuf*) ; 
 scalar_t__ packed_refs_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 struct ref_transaction* ref_store_transaction_begin (int /*<<< orphan*/ ,struct strbuf*) ; 
 scalar_t__ ref_transaction_abort (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_add_update (struct ref_transaction*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 int ref_transaction_prepare (struct ref_transaction*,struct strbuf*) ; 
 scalar_t__ ref_update_reject_duplicates (struct string_list*,struct strbuf*) ; 
 char* refs_resolve_refdup (struct ref_store*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct string_list_item* string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 struct files_transaction_backend_data* xcalloc (int,int) ; 

__attribute__((used)) static int files_transaction_prepare(struct ref_store *ref_store,
				     struct ref_transaction *transaction,
				     struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE,
			       "ref_transaction_prepare");
	size_t i;
	int ret = 0;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;
	char *head_ref = NULL;
	int head_type;
	struct files_transaction_backend_data *backend_data;
	struct ref_transaction *packed_transaction = NULL;

	assert(err);

	if (!transaction->nr)
		goto cleanup;

	backend_data = xcalloc(1, sizeof(*backend_data));
	transaction->backend_data = backend_data;

	/*
	 * Fail if a refname appears more than once in the
	 * transaction. (If we end up splitting up any updates using
	 * split_symref_update() or split_head_update(), those
	 * functions will check that the new updates don't have the
	 * same refname as any existing ones.) Also fail if any of the
	 * updates use REF_IS_PRUNING without REF_NO_DEREF.
	 */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct string_list_item *item =
			string_list_append(&affected_refnames, update->refname);

		if ((update->flags & REF_IS_PRUNING) &&
		    !(update->flags & REF_NO_DEREF))
			BUG("REF_IS_PRUNING set without REF_NO_DEREF");

		/*
		 * We store a pointer to update in item->util, but at
		 * the moment we never use the value of this field
		 * except to check whether it is non-NULL.
		 */
		item->util = update;
	}
	string_list_sort(&affected_refnames);
	if (ref_update_reject_duplicates(&affected_refnames, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/*
	 * Special hack: If a branch is updated directly and HEAD
	 * points to it (may happen on the remote side of a push
	 * for example) then logically the HEAD reflog should be
	 * updated too.
	 *
	 * A generic solution would require reverse symref lookups,
	 * but finding all symrefs pointing to a given branch would be
	 * rather costly for this rare event (the direct update of a
	 * branch) to be worth it. So let's cheat and check with HEAD
	 * only, which should cover 99% of all usage scenarios (even
	 * 100% of the default ones).
	 *
	 * So if HEAD is a symbolic reference, then record the name of
	 * the reference that it points to. If we see an update of
	 * head_ref within the transaction, then split_head_update()
	 * arranges for the reflog of HEAD to be updated, too.
	 */
	head_ref = refs_resolve_refdup(ref_store, "HEAD",
				       RESOLVE_REF_NO_RECURSE,
				       NULL, &head_type);

	if (head_ref && !(head_type & REF_ISSYMREF)) {
		FREE_AND_NULL(head_ref);
	}

	/*
	 * Acquire all locks, verify old values if provided, check
	 * that new values are valid, and write new values to the
	 * lockfiles, ready to be activated. Only keep one lockfile
	 * open at a time to avoid running out of file descriptors.
	 * Note that lock_ref_for_update() might append more updates
	 * to the transaction.
	 */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		ret = lock_ref_for_update(refs, update, transaction,
					  head_ref, &affected_refnames, err);
		if (ret)
			goto cleanup;

		if (update->flags & REF_DELETING &&
		    !(update->flags & REF_LOG_ONLY) &&
		    !(update->flags & REF_IS_PRUNING)) {
			/*
			 * This reference has to be deleted from
			 * packed-refs if it exists there.
			 */
			if (!packed_transaction) {
				packed_transaction = ref_store_transaction_begin(
						refs->packed_ref_store, err);
				if (!packed_transaction) {
					ret = TRANSACTION_GENERIC_ERROR;
					goto cleanup;
				}

				backend_data->packed_transaction =
					packed_transaction;
			}

			ref_transaction_add_update(
					packed_transaction, update->refname,
					REF_HAVE_NEW | REF_NO_DEREF,
					&update->new_oid, NULL,
					NULL);
		}
	}

	if (packed_transaction) {
		if (packed_refs_lock(refs->packed_ref_store, 0, err)) {
			ret = TRANSACTION_GENERIC_ERROR;
			goto cleanup;
		}
		backend_data->packed_refs_locked = 1;

		if (is_packed_transaction_needed(refs->packed_ref_store,
						 packed_transaction)) {
			ret = ref_transaction_prepare(packed_transaction, err);
			/*
			 * A failure during the prepare step will abort
			 * itself, but not free. Do that now, and disconnect
			 * from the files_transaction so it does not try to
			 * abort us when we hit the cleanup code below.
			 */
			if (ret) {
				ref_transaction_free(packed_transaction);
				backend_data->packed_transaction = NULL;
			}
		} else {
			/*
			 * We can skip rewriting the `packed-refs`
			 * file. But we do need to leave it locked, so
			 * that somebody else doesn't pack a reference
			 * that we are trying to delete.
			 *
			 * We need to disconnect our transaction from
			 * backend_data, since the abort (whether successful or
			 * not) will free it.
			 */
			backend_data->packed_transaction = NULL;
			if (ref_transaction_abort(packed_transaction, err)) {
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
		}
	}

cleanup:
	free(head_ref);
	string_list_clear(&affected_refnames, 0);

	if (ret)
		files_transaction_cleanup(refs, transaction);
	else
		transaction->state = REF_TRANSACTION_PREPARED;

	return ret;
}