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
struct ref_update {int flags; int /*<<< orphan*/  refname; int /*<<< orphan*/  msg; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  new_oid; } ;
struct ref_transaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int /*<<< orphan*/ ) ; 
 int REF_IS_PRUNING ; 
 int REF_LOG_ONLY ; 
 int REF_NO_DEREF ; 
 int REF_UPDATE_VIA_HEAD ; 
 int TRANSACTION_NAME_CONFLICT ; 
 struct ref_update* ref_transaction_add_update (struct ref_transaction*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ string_list_has_string (struct string_list*,char*) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int split_head_update(struct ref_update *update,
			     struct ref_transaction *transaction,
			     const char *head_ref,
			     struct string_list *affected_refnames,
			     struct strbuf *err)
{
	struct string_list_item *item;
	struct ref_update *new_update;

	if ((update->flags & REF_LOG_ONLY) ||
	    (update->flags & REF_IS_PRUNING) ||
	    (update->flags & REF_UPDATE_VIA_HEAD))
		return 0;

	if (strcmp(update->refname, head_ref))
		return 0;

	/*
	 * First make sure that HEAD is not already in the
	 * transaction. This check is O(lg N) in the transaction
	 * size, but it happens at most once per transaction.
	 */
	if (string_list_has_string(affected_refnames, "HEAD")) {
		/* An entry already existed */
		strbuf_addf(err,
			    "multiple updates for 'HEAD' (including one "
			    "via its referent '%s') are not allowed",
			    update->refname);
		return TRANSACTION_NAME_CONFLICT;
	}

	new_update = ref_transaction_add_update(
			transaction, "HEAD",
			update->flags | REF_LOG_ONLY | REF_NO_DEREF,
			&update->new_oid, &update->old_oid,
			update->msg);

	/*
	 * Add "HEAD". This insertion is O(N) in the transaction
	 * size, but it happens at most once per transaction.
	 * Add new_update->refname instead of a literal "HEAD".
	 */
	if (strcmp(new_update->refname, "HEAD"))
		BUG("%s unexpectedly not 'HEAD'", new_update->refname);
	item = string_list_insert(affected_refnames, new_update->refname);
	item->util = new_update;

	return 0;
}