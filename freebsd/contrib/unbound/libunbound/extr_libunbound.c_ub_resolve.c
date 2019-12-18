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
struct ub_result {int answer_len; int /*<<< orphan*/ * answer_packet; } ;
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  queries; int /*<<< orphan*/  finalized; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct ctx_query {TYPE_1__ node; struct ub_result* res; int /*<<< orphan*/ * msg; scalar_t__ msg_len; } ;

/* Variables and functions */
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int context_finalize (struct ub_ctx*) ; 
 struct ctx_query* context_new (struct ub_ctx*,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 int libworker_fg (struct ub_ctx*,struct ctx_query*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int 
ub_resolve(struct ub_ctx* ctx, const char* name, int rrtype, 
	int rrclass, struct ub_result** result)
{
	struct ctx_query* q;
	int r;
	*result = NULL;

	lock_basic_lock(&ctx->cfglock);
	if(!ctx->finalized) {
		r = context_finalize(ctx);
		if(r) {
			lock_basic_unlock(&ctx->cfglock);
			return r;
		}
	}
	/* create new ctx_query and attempt to add to the list */
	lock_basic_unlock(&ctx->cfglock);
	q = context_new(ctx, name, rrtype, rrclass, NULL, NULL, NULL);
	if(!q)
		return UB_NOMEM;
	/* become a resolver thread for a bit */

	r = libworker_fg(ctx, q);
	if(r) {
		lock_basic_lock(&ctx->cfglock);
		(void)rbtree_delete(&ctx->queries, q->node.key);
		context_query_delete(q);
		lock_basic_unlock(&ctx->cfglock);
		return r;
	}
	q->res->answer_packet = q->msg;
	q->res->answer_len = (int)q->msg_len;
	q->msg = NULL;
	*result = q->res;
	q->res = NULL;

	lock_basic_lock(&ctx->cfglock);
	(void)rbtree_delete(&ctx->queries, q->node.key);
	context_query_delete(q);
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}