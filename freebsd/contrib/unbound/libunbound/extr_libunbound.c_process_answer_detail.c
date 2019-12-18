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
typedef  int /*<<< orphan*/ * ub_callback_type ;
struct ub_result {int answer_len; int /*<<< orphan*/ * answer_packet; int /*<<< orphan*/  rcode; } ;
struct ub_ctx {int /*<<< orphan*/  cfglock; int /*<<< orphan*/  num_async; int /*<<< orphan*/  queries; } ;
struct regional {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct ctx_query {TYPE_1__ node; struct ub_result* res; int /*<<< orphan*/ * msg; scalar_t__ msg_len; int /*<<< orphan*/  msg_security; void* cb_arg; int /*<<< orphan*/ * cb; scalar_t__ cancelled; int /*<<< orphan*/  async; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 scalar_t__ UB_LIBCMD_ANSWER ; 
 struct ctx_query* context_deserialize_answer (struct ub_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  context_query_delete (struct ctx_query*) ; 
 scalar_t__ context_serial_getcmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libworker_enter_result (struct ub_result*,int /*<<< orphan*/ *,struct regional*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct regional* regional_create () ; 
 int /*<<< orphan*/  regional_destroy (struct regional*) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_new (scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ub_resolve_free (struct ub_result*) ; 

__attribute__((used)) static int
process_answer_detail(struct ub_ctx* ctx, uint8_t* msg, uint32_t len,
	ub_callback_type* cb, void** cbarg, int* err,
	struct ub_result** res)
{
	struct ctx_query* q;
	if(context_serial_getcmd(msg, len) != UB_LIBCMD_ANSWER) {
		log_err("error: bad data from bg worker %d",
			(int)context_serial_getcmd(msg, len));
		return 0;
	}

	lock_basic_lock(&ctx->cfglock);
	q = context_deserialize_answer(ctx, msg, len, err);
	if(!q) {
		lock_basic_unlock(&ctx->cfglock);
		/* probably simply the lookup that failed, i.e.
		 * response returned before cancel was sent out, so noerror */
		return 1;
	}
	log_assert(q->async);

	/* grab cb while locked */
	if(q->cancelled) {
		*cb = NULL;
		*cbarg = NULL;
	} else {
		*cb = q->cb;
		*cbarg = q->cb_arg;
	}
	if(*err) {
		*res = NULL;
		ub_resolve_free(q->res);
	} else {
		/* parse the message, extract rcode, fill result */
		sldns_buffer* buf = sldns_buffer_new(q->msg_len);
		struct regional* region = regional_create();
		*res = q->res;
		(*res)->rcode = LDNS_RCODE_SERVFAIL;
		if(region && buf) {
			sldns_buffer_clear(buf);
			sldns_buffer_write(buf, q->msg, q->msg_len);
			sldns_buffer_flip(buf);
			libworker_enter_result(*res, buf, region,
				q->msg_security);
		}
		(*res)->answer_packet = q->msg;
		(*res)->answer_len = (int)q->msg_len;
		q->msg = NULL;
		sldns_buffer_free(buf);
		regional_destroy(region);
	}
	q->res = NULL;
	/* delete the q from list */
	(void)rbtree_delete(&ctx->queries, q->node.key);
	ctx->num_async--;
	context_query_delete(q);
	lock_basic_unlock(&ctx->cfglock);

	if(*cb) return 2;
	ub_resolve_free(*res);
	return 1;
}