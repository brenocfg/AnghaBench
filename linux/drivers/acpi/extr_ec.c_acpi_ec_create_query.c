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
typedef  int /*<<< orphan*/  u8 ;
struct transaction {int rlen; int /*<<< orphan*/ * rdata; int /*<<< orphan*/  command; } ;
struct acpi_ec_query {struct transaction transaction; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EC_COMMAND_QUERY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_event_processor ; 
 struct acpi_ec_query* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_ec_query *acpi_ec_create_query(u8 *pval)
{
	struct acpi_ec_query *q;
	struct transaction *t;

	q = kzalloc(sizeof (struct acpi_ec_query), GFP_KERNEL);
	if (!q)
		return NULL;
	INIT_WORK(&q->work, acpi_ec_event_processor);
	t = &q->transaction;
	t->command = ACPI_EC_COMMAND_QUERY;
	t->rdata = pval;
	t->rlen = 1;
	return q;
}