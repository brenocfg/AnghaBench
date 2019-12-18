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
struct ref_update {unsigned int flags; int /*<<< orphan*/  refname; struct ref_update* parent_update; int /*<<< orphan*/  msg; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  new_oid; } ;
struct ref_transaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int /*<<< orphan*/ ) ; 
 int REF_HAVE_OLD ; 
 int REF_LOG_ONLY ; 
 int REF_NO_DEREF ; 
 unsigned int REF_UPDATE_VIA_HEAD ; 
 int TRANSACTION_NAME_CONFLICT ; 
 struct ref_update* ref_transaction_add_update (struct ref_transaction*,char const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ string_list_has_string (struct string_list*,char const*) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int split_symref_update(struct ref_update *update,
			       const char *referent,
			       struct ref_transaction *transaction,
			       struct string_list *affected_refnames,
			       struct strbuf *err)
{
	struct string_list_item *item;
	struct ref_update *new_update;
	unsigned int new_flags;

	/*
	 * First make sure that referent is not already in the
	 * transaction. This check is O(lg N) in the transaction
	 * size, but it happens at most once per symref in a
	 * transaction.
	 */
	if (string_list_has_string(affected_refnames, referent)) {
		/* An entry already exists */
		strbuf_addf(err,
			    "multiple updates for '%s' (including one "
			    "via symref '%s') are not allowed",
			    referent, update->refname);
		return TRANSACTION_NAME_CONFLICT;
	}

	new_flags = update->flags;
	if (!strcmp(update->refname, "HEAD")) {
		/*
		 * Record that the new update came via HEAD, so that
		 * when we process it, split_head_update() doesn't try
		 * to add another reflog update for HEAD. Note that
		 * this bit will be propagated if the new_update
		 * itself needs to be split.
		 */
		new_flags |= REF_UPDATE_VIA_HEAD;
	}

	new_update = ref_transaction_add_update(
			transaction, referent, new_flags,
			&update->new_oid, &update->old_oid,
			update->msg);

	new_update->parent_update = update;

	/*
	 * Change the symbolic ref update to log only. Also, it
	 * doesn't need to check its old OID value, as that will be
	 * done when new_update is processed.
	 */
	update->flags |= REF_LOG_ONLY | REF_NO_DEREF;
	update->flags &= ~REF_HAVE_OLD;

	/*
	 * Add the referent. This insertion is O(N) in the transaction
	 * size, but it happens at most once per symref in a
	 * transaction. Make sure to add new_update->refname, which will
	 * be valid as long as affected_refnames is in use, and NOT
	 * referent, which might soon be freed by our caller.
	 */
	item = string_list_insert(affected_refnames, new_update->refname);
	if (item->util)
		BUG("%s unexpectedly found in affected_refnames",
		    new_update->refname);
	item->util = new_update;

	return 0;
}