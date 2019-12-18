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
struct ub_ctx {int /*<<< orphan*/  rrpipe_lock; int /*<<< orphan*/  rr_pipe; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_PIPE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_answer (struct ub_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tube_read_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

int 
ub_process(struct ub_ctx* ctx)
{
	int r;
	uint8_t* msg;
	uint32_t len;
	while(1) {
		msg = NULL;
		lock_basic_lock(&ctx->rrpipe_lock);
		r = tube_read_msg(ctx->rr_pipe, &msg, &len, 1);
		lock_basic_unlock(&ctx->rrpipe_lock);
		if(r == 0)
			return UB_PIPE;
		else if(r == -1)
			break;
		if(!process_answer(ctx, msg, len)) {
			free(msg);
			return UB_PIPE;
		}
		free(msg);
	}
	return UB_NOERROR;
}