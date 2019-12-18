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
struct strbuf {int dummy; } ;
struct ref_update {int /*<<< orphan*/  refname; } ;
struct ref_transaction {size_t nr; int /*<<< orphan*/  state; struct ref_update** updates; struct packed_transaction_backend_data* backend_data; } ;
struct ref_store {int dummy; } ;
struct packed_transaction_backend_data {int own_lock; int /*<<< orphan*/  updates; } ;
struct packed_ref_store {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int REF_STORE_ODB ; 
 int REF_STORE_READ ; 
 int REF_STORE_WRITE ; 
 int /*<<< orphan*/  REF_TRANSACTION_PREPARED ; 
 int TRANSACTION_GENERIC_ERROR ; 
 int /*<<< orphan*/  is_lock_file_locked (int /*<<< orphan*/ *) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int,char*) ; 
 scalar_t__ packed_refs_lock (struct ref_store*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  packed_transaction_cleanup (struct packed_ref_store*,struct ref_transaction*) ; 
 scalar_t__ ref_update_reject_duplicates (int /*<<< orphan*/ *,struct strbuf*) ; 
 struct string_list_item* string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (int /*<<< orphan*/ *) ; 
 scalar_t__ write_with_updates (struct packed_ref_store*,int /*<<< orphan*/ *,struct strbuf*) ; 
 struct packed_transaction_backend_data* xcalloc (int,int) ; 

__attribute__((used)) static int packed_transaction_prepare(struct ref_store *ref_store,
				      struct ref_transaction *transaction,
				      struct strbuf *err)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ | REF_STORE_WRITE | REF_STORE_ODB,
			"ref_transaction_prepare");
	struct packed_transaction_backend_data *data;
	size_t i;
	int ret = TRANSACTION_GENERIC_ERROR;

	/*
	 * Note that we *don't* skip transactions with zero updates,
	 * because such a transaction might be executed for the side
	 * effect of ensuring that all of the references are peeled or
	 * ensuring that the `packed-refs` file is sorted. If the
	 * caller wants to optimize away empty transactions, it should
	 * do so itself.
	 */

	data = xcalloc(1, sizeof(*data));
	string_list_init(&data->updates, 0);

	transaction->backend_data = data;

	/*
	 * Stick the updates in a string list by refname so that we
	 * can sort them:
	 */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct string_list_item *item =
			string_list_append(&data->updates, update->refname);

		/* Store a pointer to update in item->util: */
		item->util = update;
	}
	string_list_sort(&data->updates);

	if (ref_update_reject_duplicates(&data->updates, err))
		goto failure;

	if (!is_lock_file_locked(&refs->lock)) {
		if (packed_refs_lock(ref_store, 0, err))
			goto failure;
		data->own_lock = 1;
	}

	if (write_with_updates(refs, &data->updates, err))
		goto failure;

	transaction->state = REF_TRANSACTION_PREPARED;
	return 0;

failure:
	packed_transaction_cleanup(refs, transaction);
	return ret;
}