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
struct rv_jit_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV_CTX_F_SEEN_TAIL_CALL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_tail_call(struct rv_jit_context *ctx)
{
	__set_bit(RV_CTX_F_SEEN_TAIL_CALL, &ctx->flags);
}