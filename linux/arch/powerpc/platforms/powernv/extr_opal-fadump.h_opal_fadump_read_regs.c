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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;
struct hdat_fadump_reg_entry {int /*<<< orphan*/  reg_num; int /*<<< orphan*/  reg_type; int /*<<< orphan*/  reg_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opal_fadump_set_regval_regnum (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void opal_fadump_read_regs(char *bufp, unsigned int regs_cnt,
					 unsigned int reg_entry_size,
					 bool cpu_endian,
					 struct pt_regs *regs)
{
	struct hdat_fadump_reg_entry *reg_entry;
	u64 val;
	int i;

	memset(regs, 0, sizeof(struct pt_regs));

	for (i = 0; i < regs_cnt; i++, bufp += reg_entry_size) {
		reg_entry = (struct hdat_fadump_reg_entry *)bufp;
		val = (cpu_endian ? be64_to_cpu(reg_entry->reg_val) :
		       reg_entry->reg_val);
		opal_fadump_set_regval_regnum(regs,
					      be32_to_cpu(reg_entry->reg_type),
					      be32_to_cpu(reg_entry->reg_num),
					      val);
	}
}