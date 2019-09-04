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
struct TYPE_2__ {int (* transaction_finish ) (struct ref_store*,struct ref_transaction*,struct strbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  REF_TRANSACTION_CLOSED 130 
#define  REF_TRANSACTION_OPEN 129 
#define  REF_TRANSACTION_PREPARED 128 
 int ref_transaction_prepare (struct ref_transaction*,struct strbuf*) ; 
 int stub1 (struct ref_store*,struct ref_transaction*,struct strbuf*) ; 

int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;
	int ret;

	switch (transaction->state) {
	case REF_TRANSACTION_OPEN:
		/* Need to prepare first. */
		ret = ref_transaction_prepare(transaction, err);
		if (ret)
			return ret;
		break;
	case REF_TRANSACTION_PREPARED:
		/* Fall through to finish. */
		break;
	case REF_TRANSACTION_CLOSED:
		BUG("commit called on a closed reference transaction");
		break;
	default:
		BUG("unexpected reference transaction state");
		break;
	}

	return refs->be->transaction_finish(refs, transaction, err);
}