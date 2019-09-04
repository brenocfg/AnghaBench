#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int buf; } ;
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  null_oid ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 scalar_t__ ref_transaction_update (struct ref_transaction*,char*,struct object_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (int,char) ; 

int update_head_with_reflog(const struct commit *old_head,
			    const struct object_id *new_head,
			    const char *action, const struct strbuf *msg,
			    struct strbuf *err)
{
	struct ref_transaction *transaction;
	struct strbuf sb = STRBUF_INIT;
	const char *nl;
	int ret = 0;

	if (action) {
		strbuf_addstr(&sb, action);
		strbuf_addstr(&sb, ": ");
	}

	nl = strchr(msg->buf, '\n');
	if (nl) {
		strbuf_add(&sb, msg->buf, nl + 1 - msg->buf);
	} else {
		strbuf_addbuf(&sb, msg);
		strbuf_addch(&sb, '\n');
	}

	transaction = ref_transaction_begin(err);
	if (!transaction ||
	    ref_transaction_update(transaction, "HEAD", new_head,
				   old_head ? &old_head->object.oid : &null_oid,
				   0, sb.buf, err) ||
	    ref_transaction_commit(transaction, err)) {
		ret = -1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&sb);

	return ret;
}