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

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 struct ref_transaction* ref_store_transaction_begin (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

struct ref_transaction *ref_transaction_begin(struct strbuf *err)
{
	return ref_store_transaction_begin(get_main_ref_store(the_repository), err);
}