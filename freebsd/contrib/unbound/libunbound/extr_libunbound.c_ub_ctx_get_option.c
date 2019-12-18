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
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_1__* env; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_SYNTAX ; 
 int config_get_option_collate (int /*<<< orphan*/ ,char const*,char**) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int
ub_ctx_get_option(struct ub_ctx* ctx, const char* opt, char** str)
{
	int r;
	lock_basic_lock(&ctx->cfglock);
	r = config_get_option_collate(ctx->env->cfg, opt, str);
	lock_basic_unlock(&ctx->cfglock);
	if(r == 0) r = UB_NOERROR;
	else if(r == 1) r = UB_SYNTAX;
	else if(r == 2) r = UB_NOMEM;
	return r;
}