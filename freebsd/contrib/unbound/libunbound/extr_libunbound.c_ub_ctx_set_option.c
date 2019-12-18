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
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_1__* env; scalar_t__ finalized; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int UB_SYNTAX ; 
 int /*<<< orphan*/  config_set_option (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int 
ub_ctx_set_option(struct ub_ctx* ctx, const char* opt, const char* val)
{
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		return UB_AFTERFINAL;
	}
	if(!config_set_option(ctx->env->cfg, opt, val)) {
		lock_basic_unlock(&ctx->cfglock);
		return UB_SYNTAX;
	}
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}