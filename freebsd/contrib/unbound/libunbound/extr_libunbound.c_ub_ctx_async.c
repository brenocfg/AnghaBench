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
struct ub_ctx {int dothread; int /*<<< orphan*/  cfglock; scalar_t__ finalized; } ;

/* Variables and functions */
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

int 
ub_ctx_async(struct ub_ctx* ctx, int dothread)
{
#ifdef THREADS_DISABLED
	if(dothread) /* cannot do threading */
		return UB_NOERROR;
#endif
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		return UB_AFTERFINAL;
	}
	ctx->dothread = dothread;
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}