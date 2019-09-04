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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_update {int flags; int type; int /*<<< orphan*/  refname; struct ref_lock* backend_data; int /*<<< orphan*/  new_oid; struct ref_update* parent_update; int /*<<< orphan*/  old_oid; } ;
struct ref_transaction {int dummy; } ;
struct ref_lock {int /*<<< orphan*/  old_oid; } ;
struct files_ref_store {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int REF_DELETING ; 
 int REF_HAVE_NEW ; 
 int REF_HAVE_OLD ; 
 int REF_ISSYMREF ; 
 int REF_LOG_ONLY ; 
 int REF_NEEDS_COMMIT ; 
 int REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 int TRANSACTION_GENERIC_ERROR ; 
 scalar_t__ check_old_oid (struct ref_update*,int /*<<< orphan*/ *,struct strbuf*) ; 
 scalar_t__ close_ref_gently (struct ref_lock*) ; 
 int /*<<< orphan*/  files_assert_main_repository (struct files_ref_store*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int lock_raw_ref (struct files_ref_store*,int /*<<< orphan*/ ,int,struct string_list*,int /*<<< orphan*/ *,struct ref_lock**,struct strbuf*,int*,struct strbuf*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  original_update_refname (struct ref_update*) ; 
 scalar_t__ refs_read_ref_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int split_head_update (struct ref_update*,struct ref_transaction*,char const*,struct string_list*,struct strbuf*) ; 
 int split_symref_update (struct ref_update*,int /*<<< orphan*/ ,struct ref_transaction*,struct string_list*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,...) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ write_ref_to_lockfile (struct ref_lock*,int /*<<< orphan*/ *,struct strbuf*) ; 

__attribute__((used)) static int lock_ref_for_update(struct files_ref_store *refs,
			       struct ref_update *update,
			       struct ref_transaction *transaction,
			       const char *head_ref,
			       struct string_list *affected_refnames,
			       struct strbuf *err)
{
	struct strbuf referent = STRBUF_INIT;
	int mustexist = (update->flags & REF_HAVE_OLD) &&
		!is_null_oid(&update->old_oid);
	int ret = 0;
	struct ref_lock *lock;

	files_assert_main_repository(refs, "lock_ref_for_update");

	if ((update->flags & REF_HAVE_NEW) && is_null_oid(&update->new_oid))
		update->flags |= REF_DELETING;

	if (head_ref) {
		ret = split_head_update(update, transaction, head_ref,
					affected_refnames, err);
		if (ret)
			goto out;
	}

	ret = lock_raw_ref(refs, update->refname, mustexist,
			   affected_refnames, NULL,
			   &lock, &referent,
			   &update->type, err);
	if (ret) {
		char *reason;

		reason = strbuf_detach(err, NULL);
		strbuf_addf(err, "cannot lock ref '%s': %s",
			    original_update_refname(update), reason);
		free(reason);
		goto out;
	}

	update->backend_data = lock;

	if (update->type & REF_ISSYMREF) {
		if (update->flags & REF_NO_DEREF) {
			/*
			 * We won't be reading the referent as part of
			 * the transaction, so we have to read it here
			 * to record and possibly check old_oid:
			 */
			if (refs_read_ref_full(&refs->base,
					       referent.buf, 0,
					       &lock->old_oid, NULL)) {
				if (update->flags & REF_HAVE_OLD) {
					strbuf_addf(err, "cannot lock ref '%s': "
						    "error reading reference",
						    original_update_refname(update));
					ret = TRANSACTION_GENERIC_ERROR;
					goto out;
				}
			} else if (check_old_oid(update, &lock->old_oid, err)) {
				ret = TRANSACTION_GENERIC_ERROR;
				goto out;
			}
		} else {
			/*
			 * Create a new update for the reference this
			 * symref is pointing at. Also, we will record
			 * and verify old_oid for this update as part
			 * of processing the split-off update, so we
			 * don't have to do it here.
			 */
			ret = split_symref_update(update,
						  referent.buf, transaction,
						  affected_refnames, err);
			if (ret)
				goto out;
		}
	} else {
		struct ref_update *parent_update;

		if (check_old_oid(update, &lock->old_oid, err)) {
			ret = TRANSACTION_GENERIC_ERROR;
			goto out;
		}

		/*
		 * If this update is happening indirectly because of a
		 * symref update, record the old OID in the parent
		 * update:
		 */
		for (parent_update = update->parent_update;
		     parent_update;
		     parent_update = parent_update->parent_update) {
			struct ref_lock *parent_lock = parent_update->backend_data;
			oidcpy(&parent_lock->old_oid, &lock->old_oid);
		}
	}

	if ((update->flags & REF_HAVE_NEW) &&
	    !(update->flags & REF_DELETING) &&
	    !(update->flags & REF_LOG_ONLY)) {
		if (!(update->type & REF_ISSYMREF) &&
		    oideq(&lock->old_oid, &update->new_oid)) {
			/*
			 * The reference already has the desired
			 * value, so we don't need to write it.
			 */
		} else if (write_ref_to_lockfile(lock, &update->new_oid,
						 err)) {
			char *write_err = strbuf_detach(err, NULL);

			/*
			 * The lock was freed upon failure of
			 * write_ref_to_lockfile():
			 */
			update->backend_data = NULL;
			strbuf_addf(err,
				    "cannot update ref '%s': %s",
				    update->refname, write_err);
			free(write_err);
			ret = TRANSACTION_GENERIC_ERROR;
			goto out;
		} else {
			update->flags |= REF_NEEDS_COMMIT;
		}
	}
	if (!(update->flags & REF_NEEDS_COMMIT)) {
		/*
		 * We didn't call write_ref_to_lockfile(), so
		 * the lockfile is still open. Close it to
		 * free up the file descriptor:
		 */
		if (close_ref_gently(lock)) {
			strbuf_addf(err, "couldn't close '%s.lock'",
				    update->refname);
			ret = TRANSACTION_GENERIC_ERROR;
			goto out;
		}
	}

out:
	strbuf_release(&referent);
	return ret;
}