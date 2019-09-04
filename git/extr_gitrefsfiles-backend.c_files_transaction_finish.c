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
struct ref_update {int flags; int type; int /*<<< orphan*/  refname; struct ref_lock* backend_data; int /*<<< orphan*/  msg; int /*<<< orphan*/  new_oid; } ;
struct ref_transaction {size_t nr; struct ref_update** updates; struct files_transaction_backend_data* backend_data; int /*<<< orphan*/  state; } ;
struct ref_store {int dummy; } ;
struct ref_lock {int /*<<< orphan*/  ref_name; int /*<<< orphan*/  old_oid; } ;
struct files_transaction_backend_data {struct ref_transaction* packed_transaction; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 int REF_DELETED_LOOSE ; 
 int REF_DELETING ; 
 int REF_ISPACKED ; 
 int REF_ISSYMREF ; 
 int REF_IS_PRUNING ; 
 int REF_LOG_ONLY ; 
 int REF_NEEDS_COMMIT ; 
 int /*<<< orphan*/  REF_TRANSACTION_CLOSED ; 
 int /*<<< orphan*/  REMOVE_EMPTY_PARENTS_REF ; 
 int /*<<< orphan*/  REMOVE_EMPTY_PARENTS_REFLOG ; 
 struct strbuf STRBUF_INIT ; 
 int TRANSACTION_GENERIC_ERROR ; 
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 int /*<<< orphan*/  clear_loose_ref_cache (struct files_ref_store*) ; 
 scalar_t__ commit_ref (struct ref_lock*) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ files_log_ref_write (struct files_ref_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct strbuf*) ; 
 int /*<<< orphan*/  files_ref_path (struct files_ref_store*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files_transaction_cleanup (struct files_ref_store*,struct ref_transaction*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  try_remove_empty_parents (struct files_ref_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlink_or_msg (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 

__attribute__((used)) static int files_transaction_finish(struct ref_store *ref_store,
				    struct ref_transaction *transaction,
				    struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 0, "ref_transaction_finish");
	size_t i;
	int ret = 0;
	struct strbuf sb = STRBUF_INIT;
	struct files_transaction_backend_data *backend_data;
	struct ref_transaction *packed_transaction;


	assert(err);

	if (!transaction->nr) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	backend_data = transaction->backend_data;
	packed_transaction = backend_data->packed_transaction;

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (update->flags & REF_NEEDS_COMMIT ||
		    update->flags & REF_LOG_ONLY) {
			if (files_log_ref_write(refs,
						lock->ref_name,
						&lock->old_oid,
						&update->new_oid,
						update->msg, update->flags,
						err)) {
				char *old_msg = strbuf_detach(err, NULL);

				strbuf_addf(err, "cannot update the ref '%s': %s",
					    lock->ref_name, old_msg);
				free(old_msg);
				unlock_ref(lock);
				update->backend_data = NULL;
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
		}
		if (update->flags & REF_NEEDS_COMMIT) {
			clear_loose_ref_cache(refs);
			if (commit_ref(lock)) {
				strbuf_addf(err, "couldn't set '%s'", lock->ref_name);
				unlock_ref(lock);
				update->backend_data = NULL;
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
		}
	}

	/*
	 * Now that updates are safely completed, we can perform
	 * deletes. First delete the reflogs of any references that
	 * will be deleted, since (in the unexpected event of an
	 * error) leaving a reference without a reflog is less bad
	 * than leaving a reflog without a reference (the latter is a
	 * mildly invalid repository state):
	 */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		if (update->flags & REF_DELETING &&
		    !(update->flags & REF_LOG_ONLY) &&
		    !(update->flags & REF_IS_PRUNING)) {
			strbuf_reset(&sb);
			files_reflog_path(refs, &sb, update->refname);
			if (!unlink_or_warn(sb.buf))
				try_remove_empty_parents(refs, update->refname,
							 REMOVE_EMPTY_PARENTS_REFLOG);
		}
	}

	/*
	 * Perform deletes now that updates are safely completed.
	 *
	 * First delete any packed versions of the references, while
	 * retaining the packed-refs lock:
	 */
	if (packed_transaction) {
		ret = ref_transaction_commit(packed_transaction, err);
		ref_transaction_free(packed_transaction);
		packed_transaction = NULL;
		backend_data->packed_transaction = NULL;
		if (ret)
			goto cleanup;
	}

	/* Now delete the loose versions of the references: */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (update->flags & REF_DELETING &&
		    !(update->flags & REF_LOG_ONLY)) {
			if (!(update->type & REF_ISPACKED) ||
			    update->type & REF_ISSYMREF) {
				/* It is a loose reference. */
				strbuf_reset(&sb);
				files_ref_path(refs, &sb, lock->ref_name);
				if (unlink_or_msg(sb.buf, err)) {
					ret = TRANSACTION_GENERIC_ERROR;
					goto cleanup;
				}
				update->flags |= REF_DELETED_LOOSE;
			}
		}
	}

	clear_loose_ref_cache(refs);

cleanup:
	files_transaction_cleanup(refs, transaction);

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if (update->flags & REF_DELETED_LOOSE) {
			/*
			 * The loose reference was deleted. Delete any
			 * empty parent directories. (Note that this
			 * can only work because we have already
			 * removed the lockfile.)
			 */
			try_remove_empty_parents(refs, update->refname,
						 REMOVE_EMPTY_PARENTS_REF);
		}
	}

	strbuf_release(&sb);
	return ret;
}