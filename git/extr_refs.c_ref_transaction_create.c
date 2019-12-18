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
 scalar_t__ is_null_oid (struct object_id const*) ; 
 int /*<<< orphan*/  null_oid ; 
 int ref_transaction_update (struct ref_transaction*,char const*,struct object_id const*,int /*<<< orphan*/ *,unsigned int,char const*,struct strbuf*) ; 

int ref_transaction_create(struct ref_transaction *transaction,
			   const char *refname,
			   const struct object_id *new_oid,
			   unsigned int flags, const char *msg,
			   struct strbuf *err)
{
	if (!new_oid || is_null_oid(new_oid))
		BUG("create called without valid new_oid");
	return ref_transaction_update(transaction, refname, new_oid,
				      &null_oid, flags, msg, err);
}