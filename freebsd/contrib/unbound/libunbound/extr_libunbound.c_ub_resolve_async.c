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
typedef  int /*<<< orphan*/  ub_callback_type ;
struct ub_ctx {int created_bg; int /*<<< orphan*/  qqpipe_lock; int /*<<< orphan*/  qq_pipe; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  num_async; int /*<<< orphan*/  queries; int /*<<< orphan*/  finalized; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct ctx_query {int querynum; TYPE_1__ node; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_PIPE ; 
 int context_finalize (struct ub_ctx*) ; 
 struct ctx_query* context_new (struct ub_ctx*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 int /*<<< orphan*/ * context_serialize_new_query (struct ctx_query*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int libworker_bg (struct ub_ctx*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_write_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
ub_resolve_async(struct ub_ctx* ctx, const char* name, int rrtype, 
	int rrclass, void* mydata, ub_callback_type callback, int* async_id)
{
	struct ctx_query* q;
	uint8_t* msg = NULL;
	uint32_t len = 0;

	if(async_id)
		*async_id = 0;
	lock_basic_lock(&ctx->cfglock);
	if(!ctx->finalized) {
		int r = context_finalize(ctx);
		if(r) {
			lock_basic_unlock(&ctx->cfglock);
			return r;
		}
	}
	if(!ctx->created_bg) {
		int r;
		ctx->created_bg = 1;
		lock_basic_unlock(&ctx->cfglock);
		r = libworker_bg(ctx);
		if(r) {
			lock_basic_lock(&ctx->cfglock);
			ctx->created_bg = 0;
			lock_basic_unlock(&ctx->cfglock);
			return r;
		}
	} else {
		lock_basic_unlock(&ctx->cfglock);
	}

	/* create new ctx_query and attempt to add to the list */
	q = context_new(ctx, name, rrtype, rrclass, callback, NULL, mydata);
	if(!q)
		return UB_NOMEM;

	/* write over pipe to background worker */
	lock_basic_lock(&ctx->cfglock);
	msg = context_serialize_new_query(q, &len);
	if(!msg) {
		(void)rbtree_delete(&ctx->queries, q->node.key);
		ctx->num_async--;
		context_query_delete(q);
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOMEM;
	}
	if(async_id)
		*async_id = q->querynum;
	lock_basic_unlock(&ctx->cfglock);
	
	lock_basic_lock(&ctx->qqpipe_lock);
	if(!tube_write_msg(ctx->qq_pipe, msg, len, 0)) {
		lock_basic_unlock(&ctx->qqpipe_lock);
		free(msg);
		return UB_PIPE;
	}
	lock_basic_unlock(&ctx->qqpipe_lock);
	free(msg);
	return UB_NOERROR;
}