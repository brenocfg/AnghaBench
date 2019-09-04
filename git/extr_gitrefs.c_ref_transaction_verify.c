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
struct strbuf {int dummy; } ;
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int ref_transaction_update (struct ref_transaction*,char const*,int /*<<< orphan*/ *,struct object_id const*,unsigned int,int /*<<< orphan*/ *,struct strbuf*) ; 

int ref_transaction_verify(struct ref_transaction *transaction,
			   const char *refname,
			   const struct object_id *old_oid,
			   unsigned int flags,
			   struct strbuf *err)
{
	if (!old_oid)
		BUG("verify called with old_oid set to NULL");
	return ref_transaction_update(transaction, refname,
				      NULL, old_oid,
				      flags, NULL, err);
}