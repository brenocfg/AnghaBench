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
struct ref_update {struct ref_lock* backend_data; } ;
struct ref_transaction {size_t nr; int /*<<< orphan*/  state; struct ref_update** updates; struct files_transaction_backend_data* backend_data; } ;
struct ref_lock {int dummy; } ;
struct files_transaction_backend_data {scalar_t__ packed_refs_locked; scalar_t__ packed_transaction; } ;
struct files_ref_store {int /*<<< orphan*/  packed_ref_store; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TRANSACTION_CLOSED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct files_transaction_backend_data*) ; 
 int /*<<< orphan*/  packed_refs_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ref_transaction_abort (scalar_t__,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 

__attribute__((used)) static void files_transaction_cleanup(struct files_ref_store *refs,
				      struct ref_transaction *transaction)
{
	size_t i;
	struct files_transaction_backend_data *backend_data =
		transaction->backend_data;
	struct strbuf err = STRBUF_INIT;

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (lock) {
			unlock_ref(lock);
			update->backend_data = NULL;
		}
	}

	if (backend_data->packed_transaction &&
	    ref_transaction_abort(backend_data->packed_transaction, &err)) {
		error("error aborting transaction: %s", err.buf);
		strbuf_release(&err);
	}

	if (backend_data->packed_refs_locked)
		packed_refs_unlock(refs->packed_ref_store);

	free(backend_data);

	transaction->state = REF_TRANSACTION_CLOSED;
}