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
struct kvm_coproc_target_table {size_t target; int /*<<< orphan*/  num; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_reg_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_coproc_target_table** target_tables ; 

void kvm_register_target_coproc_table(struct kvm_coproc_target_table *table)
{
	BUG_ON(check_reg_table(table->table, table->num));
	target_tables[table->target] = table;
}