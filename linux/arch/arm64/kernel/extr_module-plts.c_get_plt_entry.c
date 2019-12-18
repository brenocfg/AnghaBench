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
typedef  scalar_t__ u32 ;
struct plt_entry {int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_BRANCH_NOLINK ; 
 int /*<<< orphan*/  AARCH64_INSN_REG_16 ; 
 struct plt_entry __get_adrp_add_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ aarch64_insn_gen_branch_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

struct plt_entry get_plt_entry(u64 dst, void *pc)
{
	struct plt_entry plt;
	static u32 br;

	if (!br)
		br = aarch64_insn_gen_branch_reg(AARCH64_INSN_REG_16,
						 AARCH64_INSN_BRANCH_NOLINK);

	plt = __get_adrp_add_pair(dst, (u64)pc, AARCH64_INSN_REG_16);
	plt.br = cpu_to_le32(br);

	return plt;
}