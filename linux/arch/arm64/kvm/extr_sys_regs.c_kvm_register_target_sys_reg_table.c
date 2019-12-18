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
struct kvm_sys_reg_target_table {int dummy; } ;

/* Variables and functions */
 struct kvm_sys_reg_target_table** target_tables ; 

void kvm_register_target_sys_reg_table(unsigned int target,
				       struct kvm_sys_reg_target_table *table)
{
	target_tables[target] = table;
}