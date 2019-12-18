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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  (* ub_callback_type ) (void*,int,struct ub_result*) ;
struct ub_result {int dummy; } ;
struct ub_ctx {scalar_t__ num_async; int /*<<< orphan*/  rrpipe_lock; int /*<<< orphan*/  rr_pipe; int /*<<< orphan*/  cfglock; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_PIPE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int process_answer_detail (struct ub_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,int,struct ub_result*),void**,int*,struct ub_result**) ; 
 int /*<<< orphan*/  stub1 (void*,int,struct ub_result*) ; 
 int tube_read_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int tube_wait (int /*<<< orphan*/ ) ; 

int 
ub_wait(struct ub_ctx* ctx)
{
	int err;
	ub_callback_type cb;
	void* cbarg;
	struct ub_result* res;
	int r;
	uint8_t* msg;
	uint32_t len;
	/* this is basically the same loop as _process(), but with changes.
	 * holds the rrpipe lock and waits with tube_wait */
	while(1) {
		lock_basic_lock(&ctx->rrpipe_lock);
		lock_basic_lock(&ctx->cfglock);
		if(ctx->num_async == 0) {
			lock_basic_unlock(&ctx->cfglock);
			lock_basic_unlock(&ctx->rrpipe_lock);
			break;
		}
		lock_basic_unlock(&ctx->cfglock);

		/* keep rrpipe locked, while
		 * 	o waiting for pipe readable
		 * 	o parsing message
		 * 	o possibly decrementing num_async
		 * do callback without lock
		 */
		r = tube_wait(ctx->rr_pipe);
		if(r) {
			r = tube_read_msg(ctx->rr_pipe, &msg, &len, 1);
			if(r == 0) {
				lock_basic_unlock(&ctx->rrpipe_lock);
				return UB_PIPE;
			}
			if(r == -1) {
				lock_basic_unlock(&ctx->rrpipe_lock);
				continue;
			}
			r = process_answer_detail(ctx, msg, len, 
				&cb, &cbarg, &err, &res);
			lock_basic_unlock(&ctx->rrpipe_lock);
			free(msg);
			if(r == 0)
				return UB_PIPE;
			if(r == 2)
				(*cb)(cbarg, err, res);
		} else {
			lock_basic_unlock(&ctx->rrpipe_lock);
		}
	}
	return UB_NOERROR;
}