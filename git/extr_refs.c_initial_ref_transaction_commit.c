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
struct ref_transaction {struct ref_store* ref_store; } ;
struct ref_store {TYPE_1__* be; } ;
struct TYPE_2__ {int (* initial_transaction_commit ) (struct ref_store*,struct ref_transaction*,struct strbuf*) ;} ;

/* Variables and functions */
 int stub1 (struct ref_store*,struct ref_transaction*,struct strbuf*) ; 

int initial_ref_transaction_commit(struct ref_transaction *transaction,
				   struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;

	return refs->be->initial_transaction_commit(refs, transaction, err);
}