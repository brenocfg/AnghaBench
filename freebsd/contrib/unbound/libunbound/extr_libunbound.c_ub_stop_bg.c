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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  bg_pid; int /*<<< orphan*/  bg_tid; scalar_t__ dothread; int /*<<< orphan*/  rrpipe_lock; int /*<<< orphan*/  rr_pipe; int /*<<< orphan*/  qqpipe_lock; int /*<<< orphan*/  qq_pipe; scalar_t__ created_bg; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ UB_LIBCMD_QUIT ; 
 scalar_t__ context_serial_getcmd (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ tube_read_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_write_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_thread_join (int /*<<< orphan*/ ) ; 
 int verbosity ; 
 int waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ub_stop_bg(struct ub_ctx* ctx)
{
	/* stop the bg thread */
	lock_basic_lock(&ctx->cfglock);
	if(ctx->created_bg) {
		uint8_t* msg;
		uint32_t len;
		uint32_t cmd = UB_LIBCMD_QUIT;
		lock_basic_unlock(&ctx->cfglock);
		lock_basic_lock(&ctx->qqpipe_lock);
		(void)tube_write_msg(ctx->qq_pipe, (uint8_t*)&cmd, 
			(uint32_t)sizeof(cmd), 0);
		lock_basic_unlock(&ctx->qqpipe_lock);
		lock_basic_lock(&ctx->rrpipe_lock);
		while(tube_read_msg(ctx->rr_pipe, &msg, &len, 0)) {
			/* discard all results except a quit confirm */
			if(context_serial_getcmd(msg, len) == UB_LIBCMD_QUIT) {
				free(msg);
				break;
			}
			free(msg);
		}
		lock_basic_unlock(&ctx->rrpipe_lock);

		/* if bg worker is a thread, wait for it to exit, so that all
	 	 * resources are really gone. */
		lock_basic_lock(&ctx->cfglock);
		if(ctx->dothread) {
			lock_basic_unlock(&ctx->cfglock);
			ub_thread_join(ctx->bg_tid);
		} else {
			lock_basic_unlock(&ctx->cfglock);
#ifndef UB_ON_WINDOWS
			if(waitpid(ctx->bg_pid, NULL, 0) == -1) {
				if(verbosity > 2)
					log_err("waitpid: %s", strerror(errno));
			}
#endif
		}
	}
	else {
		lock_basic_unlock(&ctx->cfglock);
	}
}