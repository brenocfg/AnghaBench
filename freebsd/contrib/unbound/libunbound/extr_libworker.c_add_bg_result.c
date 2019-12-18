#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct libworker {TYPE_3__* ctx; scalar_t__ is_bg_thread; scalar_t__ want_quit; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct ctx_query {TYPE_2__ node; TYPE_1__* res; int /*<<< orphan*/  msg; int /*<<< orphan*/  msg_len; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_6__ {int /*<<< orphan*/  rr_pipe; int /*<<< orphan*/  num_async; int /*<<< orphan*/  queries; int /*<<< orphan*/  cfglock; } ;
struct TYPE_4__ {int was_ratelimited; void* why_bogus; } ;

/* Variables and functions */
 int UB_NOMEM ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 int /*<<< orphan*/ * context_serialize_answer (struct ctx_query*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  tube_queue_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_bg_result(struct libworker* w, struct ctx_query* q, sldns_buffer* pkt, 
	int err, char* reason, int was_ratelimited)
{
	uint8_t* msg = NULL;
	uint32_t len = 0;

	if(w->want_quit) {
		context_query_delete(q);
		return;
	}
	/* serialize and delete unneeded q */
	if(w->is_bg_thread) {
		lock_basic_lock(&w->ctx->cfglock);
		if(reason)
			q->res->why_bogus = strdup(reason);
		q->res->was_ratelimited = was_ratelimited;
		if(pkt) {
			q->msg_len = sldns_buffer_remaining(pkt);
			q->msg = memdup(sldns_buffer_begin(pkt), q->msg_len);
			if(!q->msg) {
				msg = context_serialize_answer(q, UB_NOMEM, NULL, &len);
			} else {
				msg = context_serialize_answer(q, err, NULL, &len);
			}
		} else {
			msg = context_serialize_answer(q, err, NULL, &len);
		}
		lock_basic_unlock(&w->ctx->cfglock);
	} else {
		if(reason)
			q->res->why_bogus = strdup(reason);
		q->res->was_ratelimited = was_ratelimited;
		msg = context_serialize_answer(q, err, pkt, &len);
		(void)rbtree_delete(&w->ctx->queries, q->node.key);
		w->ctx->num_async--;
		context_query_delete(q);
	}

	if(!msg) {
		log_err("out of memory for async answer");
		return;
	}
	if(!tube_queue_item(w->ctx->rr_pipe, msg, len)) {
		log_err("out of memory for async answer");
		return;
	}
}