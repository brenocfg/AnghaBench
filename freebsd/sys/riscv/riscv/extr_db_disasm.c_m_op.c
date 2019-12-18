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
typedef  int uint32_t ;
struct riscv_op {int match; int mask; } ;

/* Variables and functions */

__attribute__((used)) static int
m_op(struct riscv_op *op, uint32_t insn)
{

	if (((insn ^ op->match) & op->mask) == 0)
		return (1);

	return (0);
}