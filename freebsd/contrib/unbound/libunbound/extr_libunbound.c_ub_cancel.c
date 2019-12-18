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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  qqpipe_lock; int /*<<< orphan*/  qq_pipe; int /*<<< orphan*/  num_async; int /*<<< orphan*/  queries; int /*<<< orphan*/  dothread; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct ctx_query {int cancelled; TYPE_1__ node; int /*<<< orphan*/  async; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_NOID ; 
 int UB_NOMEM ; 
 int UB_PIPE ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 int /*<<< orphan*/ * context_serialize_cancel (struct ctx_query*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tube_write_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
ub_cancel(struct ub_ctx* ctx, int async_id)
{
	struct ctx_query* q;
	uint8_t* msg = NULL;
	uint32_t len = 0;
	lock_basic_lock(&ctx->cfglock);
	q = (struct ctx_query*)rbtree_search(&ctx->queries, &async_id);
	if(!q || !q->async) {
		/* it is not there, so nothing to do */
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOID;
	}
	log_assert(q->async);
	q->cancelled = 1;
	
	/* delete it */
	if(!ctx->dothread) { /* if forked */
		(void)rbtree_delete(&ctx->queries, q->node.key);
		ctx->num_async--;
		msg = context_serialize_cancel(q, &len);
		context_query_delete(q);
		lock_basic_unlock(&ctx->cfglock);
		if(!msg) {
			return UB_NOMEM;
		}
		/* send cancel to background worker */
		lock_basic_lock(&ctx->qqpipe_lock);
		if(!tube_write_msg(ctx->qq_pipe, msg, len, 0)) {
			lock_basic_unlock(&ctx->qqpipe_lock);
			free(msg);
			return UB_PIPE;
		}
		lock_basic_unlock(&ctx->qqpipe_lock);
		free(msg);
	} else {
		lock_basic_unlock(&ctx->cfglock);
	}
	return UB_NOERROR;
}