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
struct ref_transaction {struct ref_store* ref_store; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 struct ref_transaction* xcalloc (int,int) ; 

struct ref_transaction *ref_store_transaction_begin(struct ref_store *refs,
						    struct strbuf *err)
{
	struct ref_transaction *tr;
	assert(err);

	tr = xcalloc(1, sizeof(struct ref_transaction));
	tr->ref_store = refs;
	return tr;
}