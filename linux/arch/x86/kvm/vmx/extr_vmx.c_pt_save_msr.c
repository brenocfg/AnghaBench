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
typedef  int u32 ;
struct pt_ctx {int /*<<< orphan*/ * addr_b; int /*<<< orphan*/ * addr_a; int /*<<< orphan*/  cr3_match; int /*<<< orphan*/  output_mask; int /*<<< orphan*/  output_base; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ MSR_IA32_RTIT_ADDR0_A ; 
 scalar_t__ MSR_IA32_RTIT_ADDR0_B ; 
 scalar_t__ MSR_IA32_RTIT_CR3_MATCH ; 
 scalar_t__ MSR_IA32_RTIT_OUTPUT_BASE ; 
 scalar_t__ MSR_IA32_RTIT_OUTPUT_MASK ; 
 scalar_t__ MSR_IA32_RTIT_STATUS ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pt_save_msr(struct pt_ctx *ctx, u32 addr_range)
{
	u32 i;

	rdmsrl(MSR_IA32_RTIT_STATUS, ctx->status);
	rdmsrl(MSR_IA32_RTIT_OUTPUT_BASE, ctx->output_base);
	rdmsrl(MSR_IA32_RTIT_OUTPUT_MASK, ctx->output_mask);
	rdmsrl(MSR_IA32_RTIT_CR3_MATCH, ctx->cr3_match);
	for (i = 0; i < addr_range; i++) {
		rdmsrl(MSR_IA32_RTIT_ADDR0_A + i * 2, ctx->addr_a[i]);
		rdmsrl(MSR_IA32_RTIT_ADDR0_B + i * 2, ctx->addr_b[i]);
	}
}