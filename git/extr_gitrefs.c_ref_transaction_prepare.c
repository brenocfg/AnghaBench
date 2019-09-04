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
struct strbuf {int dummy; } ;
struct ref_transaction {int state; struct ref_store* ref_store; } ;
struct ref_store {TYPE_1__* be; } ;
struct TYPE_2__ {int (* transaction_prepare ) (struct ref_store*,struct ref_transaction*,struct strbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  GIT_QUARANTINE_ENVIRONMENT ; 
#define  REF_TRANSACTION_CLOSED 130 
#define  REF_TRANSACTION_OPEN 129 
#define  REF_TRANSACTION_PREPARED 128 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ref_store*,struct ref_transaction*,struct strbuf*) ; 

int ref_transaction_prepare(struct ref_transaction *transaction,
			    struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;

	switch (transaction->state) {
	case REF_TRANSACTION_OPEN:
		/* Good. */
		break;
	case REF_TRANSACTION_PREPARED:
		BUG("prepare called twice on reference transaction");
		break;
	case REF_TRANSACTION_CLOSED:
		BUG("prepare called on a closed reference transaction");
		break;
	default:
		BUG("unexpected reference transaction state");
		break;
	}

	if (getenv(GIT_QUARANTINE_ENVIRONMENT)) {
		strbuf_addstr(err,
			      _("ref updates forbidden inside quarantine environment"));
		return -1;
	}

	return refs->be->transaction_prepare(refs, transaction, err);
}