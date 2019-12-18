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
struct ref_transaction {int /*<<< orphan*/  state; struct packed_transaction_backend_data* backend_data; } ;
struct packed_transaction_backend_data {scalar_t__ own_lock; int /*<<< orphan*/  updates; } ;
struct packed_ref_store {int /*<<< orphan*/  base; int /*<<< orphan*/  lock; int /*<<< orphan*/  tempfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TRANSACTION_CLOSED ; 
 int /*<<< orphan*/  delete_tempfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct packed_transaction_backend_data*) ; 
 scalar_t__ is_lock_file_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ is_tempfile_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_refs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void packed_transaction_cleanup(struct packed_ref_store *refs,
				       struct ref_transaction *transaction)
{
	struct packed_transaction_backend_data *data = transaction->backend_data;

	if (data) {
		string_list_clear(&data->updates, 0);

		if (is_tempfile_active(refs->tempfile))
			delete_tempfile(&refs->tempfile);

		if (data->own_lock && is_lock_file_locked(&refs->lock)) {
			packed_refs_unlock(&refs->base);
			data->own_lock = 0;
		}

		free(data);
		transaction->backend_data = NULL;
	}

	transaction->state = REF_TRANSACTION_CLOSED;
}