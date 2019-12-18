#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  num_async; int /*<<< orphan*/  queries; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct ctx_query {int msg_security; TYPE_4__* w; TYPE_2__ node; scalar_t__ cancelled; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;
struct TYPE_8__ {TYPE_3__* env; struct ub_ctx* ctx; scalar_t__ is_bg_thread; TYPE_1__* back; } ;
struct TYPE_7__ {int /*<<< orphan*/ * scratch_buffer; } ;
struct TYPE_5__ {scalar_t__ want_to_quit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RD ; 
 int /*<<< orphan*/  UB_NOERROR ; 
 int /*<<< orphan*/  add_bg_result (TYPE_4__*,struct ctx_query*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 int /*<<< orphan*/  error_encode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
libworker_bg_done_cb(void* arg, int rcode, sldns_buffer* buf, enum sec_status s,
	char* why_bogus, int was_ratelimited)
{
	struct ctx_query* q = (struct ctx_query*)arg;

	if(q->cancelled || q->w->back->want_to_quit) {
		if(q->w->is_bg_thread) {
			/* delete it now */
			struct ub_ctx* ctx = q->w->ctx;
			lock_basic_lock(&ctx->cfglock);
			(void)rbtree_delete(&ctx->queries, q->node.key);
			ctx->num_async--;
			context_query_delete(q);
			lock_basic_unlock(&ctx->cfglock);
		}
		/* cancelled, do not give answer */
		return;
	}
	q->msg_security = s;
	if(!buf) {
		buf = q->w->env->scratch_buffer;
	}
	if(rcode != 0) {
		error_encode(buf, rcode, NULL, 0, BIT_RD, NULL);
	}
	add_bg_result(q->w, q, buf, UB_NOERROR, why_bogus, was_ratelimited);
}