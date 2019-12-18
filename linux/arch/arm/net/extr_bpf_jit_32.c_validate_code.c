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
struct jit_ctx {int idx; scalar_t__* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_INST_UDF ; 
 scalar_t__ __opcode_to_mem_arm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_code(struct jit_ctx *ctx)
{
	int i;

	for (i = 0; i < ctx->idx; i++) {
		if (ctx->target[i] == __opcode_to_mem_arm(ARM_INST_UDF))
			return -1;
	}

	return 0;
}