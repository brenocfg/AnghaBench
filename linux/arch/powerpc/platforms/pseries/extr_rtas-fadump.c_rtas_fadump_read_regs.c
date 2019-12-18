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
struct rtas_fadump_reg_entry {int /*<<< orphan*/  reg_value; int /*<<< orphan*/  reg_id; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ fadump_str_to_u64 (char*) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtas_fadump_set_regval (struct pt_regs*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct rtas_fadump_reg_entry*
rtas_fadump_read_regs(struct rtas_fadump_reg_entry *reg_entry,
		      struct pt_regs *regs)
{
	memset(regs, 0, sizeof(struct pt_regs));

	while (be64_to_cpu(reg_entry->reg_id) != fadump_str_to_u64("CPUEND")) {
		rtas_fadump_set_regval(regs, be64_to_cpu(reg_entry->reg_id),
				       be64_to_cpu(reg_entry->reg_value));
		reg_entry++;
	}
	reg_entry++;
	return reg_entry;
}