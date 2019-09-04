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
struct ref_store {int dummy; } ;
struct packed_ref_store {int dummy; } ;

/* Variables and functions */
 int REF_STORE_ODB ; 
 int REF_STORE_READ ; 
 int REF_STORE_WRITE ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int,char*) ; 
 int /*<<< orphan*/  packed_transaction_cleanup (struct packed_ref_store*,struct ref_transaction*) ; 

__attribute__((used)) static int packed_transaction_abort(struct ref_store *ref_store,
				    struct ref_transaction *transaction,
				    struct strbuf *err)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ | REF_STORE_WRITE | REF_STORE_ODB,
			"ref_transaction_abort");

	packed_transaction_cleanup(refs, transaction);
	return 0;
}