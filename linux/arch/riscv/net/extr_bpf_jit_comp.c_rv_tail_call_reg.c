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
struct rv_jit_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV_CTX_F_SEEN_S6 ; 
 int /*<<< orphan*/  RV_REG_A6 ; 
 int /*<<< orphan*/  RV_REG_S6 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_tail_call (struct rv_jit_context*) ; 
 scalar_t__ seen_call (struct rv_jit_context*) ; 

__attribute__((used)) static u8 rv_tail_call_reg(struct rv_jit_context *ctx)
{
	mark_tail_call(ctx);

	if (seen_call(ctx)) {
		__set_bit(RV_CTX_F_SEEN_S6, &ctx->flags);
		return RV_REG_S6;
	}
	return RV_REG_A6;
}