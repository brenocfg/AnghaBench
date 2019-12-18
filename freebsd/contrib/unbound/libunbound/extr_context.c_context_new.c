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
typedef  int /*<<< orphan*/ * ub_event_callback_type ;
typedef  int /*<<< orphan*/ * ub_callback_type ;
struct TYPE_2__ {int /*<<< orphan*/ * key; } ;
struct ub_result {int async; int qtype; int qclass; TYPE_1__ node; struct ub_result* res; int /*<<< orphan*/  qname; void* cb_arg; int /*<<< orphan*/ * cb_event; int /*<<< orphan*/ * cb; int /*<<< orphan*/  querynum; } ;
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  queries; int /*<<< orphan*/  num_async; } ;
struct ctx_query {int async; int qtype; int qclass; TYPE_1__ node; struct ctx_query* res; int /*<<< orphan*/  qname; void* cb_arg; int /*<<< orphan*/ * cb_event; int /*<<< orphan*/ * cb; int /*<<< orphan*/  querynum; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  find_id (struct ub_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ub_result*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct ctx_query* 
context_new(struct ub_ctx* ctx, const char* name, int rrtype, int rrclass, 
	ub_callback_type cb, ub_event_callback_type cb_event, void* cbarg)
{
	struct ctx_query* q = (struct ctx_query*)calloc(1, sizeof(*q));
	if(!q) return NULL;
	lock_basic_lock(&ctx->cfglock);
	if(!find_id(ctx, &q->querynum)) {
		lock_basic_unlock(&ctx->cfglock);
		free(q);
		return NULL;
	}
	lock_basic_unlock(&ctx->cfglock);
	q->node.key = &q->querynum;
	q->async = (cb != NULL || cb_event != NULL);
	q->cb = cb;
	q->cb_event = cb_event;
	q->cb_arg = cbarg;
	q->res = (struct ub_result*)calloc(1, sizeof(*q->res));
	if(!q->res) {
		free(q);
		return NULL;
	}
	q->res->qname = strdup(name);
	if(!q->res->qname) {
		free(q->res);
		free(q);
		return NULL;
	}
	q->res->qtype = rrtype;
	q->res->qclass = rrclass;

	/* add to query list */
	lock_basic_lock(&ctx->cfglock);
	if(q->async)
		ctx->num_async ++;
	(void)rbtree_insert(&ctx->queries, &q->node);
	lock_basic_unlock(&ctx->cfglock);
	return q;
}