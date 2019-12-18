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
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  finalized; } ;

/* Variables and functions */
 int context_finalize (struct ub_ctx*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ub_ctx_finalize(struct ub_ctx* ctx)
{
	int res = 0;
	lock_basic_lock(&ctx->cfglock);
	if (!ctx->finalized) {
		res = context_finalize(ctx);
	}
	lock_basic_unlock(&ctx->cfglock);
	return res;
}