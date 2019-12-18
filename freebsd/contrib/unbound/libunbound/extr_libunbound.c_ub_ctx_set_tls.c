#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_2__* env; scalar_t__ finalized; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int ssl_upstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int ub_ctx_set_tls(struct ub_ctx* ctx, int tls)
{
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		errno=EINVAL;
		return UB_AFTERFINAL;
	}
	ctx->env->cfg->ssl_upstream = tls;
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}