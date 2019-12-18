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
struct repository {int dummy; } ;
struct ref_transaction {int dummy; } ;
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (char*,...) ; 
 struct ref_store* get_main_ref_store (struct repository*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  rebase_path_refs_to_delete () ; 
 struct ref_transaction* ref_store_transaction_begin (struct ref_store*,struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int safe_append (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int do_label(struct repository *r, const char *name, int len)
{
	struct ref_store *refs = get_main_ref_store(r);
	struct ref_transaction *transaction;
	struct strbuf ref_name = STRBUF_INIT, err = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
	int ret = 0;
	struct object_id head_oid;

	if (len == 1 && *name == '#')
		return error(_("illegal label name: '%.*s'"), len, name);

	strbuf_addf(&ref_name, "refs/rewritten/%.*s", len, name);
	strbuf_addf(&msg, "rebase -i (label) '%.*s'", len, name);

	transaction = ref_store_transaction_begin(refs, &err);
	if (!transaction) {
		error("%s", err.buf);
		ret = -1;
	} else if (get_oid("HEAD", &head_oid)) {
		error(_("could not read HEAD"));
		ret = -1;
	} else if (ref_transaction_update(transaction, ref_name.buf, &head_oid,
					  NULL, 0, msg.buf, &err) < 0 ||
		   ref_transaction_commit(transaction, &err)) {
		error("%s", err.buf);
		ret = -1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	strbuf_release(&msg);

	if (!ret)
		ret = safe_append(rebase_path_refs_to_delete(),
				  "%s\n", ref_name.buf);
	strbuf_release(&ref_name);

	return ret;
}