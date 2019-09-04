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
struct tag {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; struct tag* next_tag; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_transaction {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure ; 
 struct tag* first_tag ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void dump_tags(void)
{
	static const char *msg = "fast-import";
	struct tag *t;
	struct strbuf ref_name = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;
	struct ref_transaction *transaction;

	transaction = ref_transaction_begin(&err);
	if (!transaction) {
		failure |= error("%s", err.buf);
		goto cleanup;
	}
	for (t = first_tag; t; t = t->next_tag) {
		strbuf_reset(&ref_name);
		strbuf_addf(&ref_name, "refs/tags/%s", t->name);

		if (ref_transaction_update(transaction, ref_name.buf,
					   &t->oid, NULL, 0, msg, &err)) {
			failure |= error("%s", err.buf);
			goto cleanup;
		}
	}
	if (ref_transaction_commit(transaction, &err))
		failure |= error("%s", err.buf);

 cleanup:
	ref_transaction_free(transaction);
	strbuf_release(&ref_name);
	strbuf_release(&err);
}