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
struct strbuf {int dummy; } ;
struct ref_update {int flags; int /*<<< orphan*/  refname; int /*<<< orphan*/  new_oid; } ;
struct ref_transaction {size_t nr; struct ref_update** updates; } ;
struct ref_store {int dummy; } ;
struct packed_ref_store {int /*<<< orphan*/  lock; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ ENOENT ; 
 int REF_HAVE_NEW ; 
 int REF_HAVE_OLD ; 
 int /*<<< orphan*/  REF_STORE_READ ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  is_lock_file_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  refs_read_raw_ref (struct ref_store*,int /*<<< orphan*/ ,struct object_id*,struct strbuf*,unsigned int*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int is_packed_transaction_needed(struct ref_store *ref_store,
				 struct ref_transaction *transaction)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ,
			"is_packed_transaction_needed");
	struct strbuf referent = STRBUF_INIT;
	size_t i;
	int ret;

	if (!is_lock_file_locked(&refs->lock))
		BUG("is_packed_transaction_needed() called while unlocked");

	/*
	 * We're only going to bother returning false for the common,
	 * trivial case that references are only being deleted, their
	 * old values are not being checked, and the old `packed-refs`
	 * file doesn't contain any of those reference(s). This gives
	 * false positives for some other cases that could
	 * theoretically be optimized away:
	 *
	 * 1. It could be that the old value is being verified without
	 *    setting a new value. In this case, we could verify the
	 *    old value here and skip the update if it agrees. If it
	 *    disagrees, we could either let the update go through
	 *    (the actual commit would re-detect and report the
	 *    problem), or come up with a way of reporting such an
	 *    error to *our* caller.
	 *
	 * 2. It could be that a new value is being set, but that it
	 *    is identical to the current packed value of the
	 *    reference.
	 *
	 * Neither of these cases will come up in the current code,
	 * because the only caller of this function passes to it a
	 * transaction that only includes `delete` updates with no
	 * `old_id`. Even if that ever changes, false positives only
	 * cause an optimization to be missed; they do not affect
	 * correctness.
	 */

	/*
	 * Start with the cheap checks that don't require old
	 * reference values to be read:
	 */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if (update->flags & REF_HAVE_OLD)
			/* Have to check the old value -> needed. */
			return 1;

		if ((update->flags & REF_HAVE_NEW) && !is_null_oid(&update->new_oid))
			/* Have to set a new value -> needed. */
			return 1;
	}

	/*
	 * The transaction isn't checking any old values nor is it
	 * setting any nonzero new values, so it still might be able
	 * to be skipped. Now do the more expensive check: the update
	 * is needed if any of the updates is a delete, and the old
	 * `packed-refs` file contains a value for that reference.
	 */
	ret = 0;
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		unsigned int type;
		struct object_id oid;

		if (!(update->flags & REF_HAVE_NEW))
			/*
			 * This reference isn't being deleted -> not
			 * needed.
			 */
			continue;

		if (!refs_read_raw_ref(ref_store, update->refname,
				       &oid, &referent, &type) ||
		    errno != ENOENT) {
			/*
			 * We have to actually delete that reference
			 * -> this transaction is needed.
			 */
			ret = 1;
			break;
		}
	}

	strbuf_release(&referent);
	return ret;
}