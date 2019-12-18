#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x86_emulate_ctxt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;
struct operand {scalar_t__ type; TYPE_1__ addr; int /*<<< orphan*/  mm_val; } ;

/* Variables and functions */
 scalar_t__ OP_MM ; 
 int /*<<< orphan*/  read_mmx_reg (struct x86_emulate_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fetch_possible_mmx_operand(struct x86_emulate_ctxt *ctxt,
				       struct operand *op)
{
	if (op->type == OP_MM)
		read_mmx_reg(ctxt, &op->mm_val, op->addr.mm);
}