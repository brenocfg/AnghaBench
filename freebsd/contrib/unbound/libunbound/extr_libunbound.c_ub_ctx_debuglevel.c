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
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_2__* env; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int verbosity; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int verbosity ; 

int
ub_ctx_debuglevel(struct ub_ctx* ctx, int d)
{
	lock_basic_lock(&ctx->cfglock);
	verbosity = d;
	ctx->env->cfg->verbosity = d;
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}