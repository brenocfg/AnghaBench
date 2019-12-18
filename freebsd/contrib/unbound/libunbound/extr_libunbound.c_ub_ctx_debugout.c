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
struct ub_ctx {int logfile_override; int /*<<< orphan*/  cfglock; void* log_out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int UB_NOERROR ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_file (int /*<<< orphan*/ *) ; 

int ub_ctx_debugout(struct ub_ctx* ctx, void* out)
{
	lock_basic_lock(&ctx->cfglock);
	log_file((FILE*)out);
	ctx->logfile_override = 1;
	ctx->log_out = out;
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}