#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct query_info {int /*<<< orphan*/ * qname; } ;
struct libworker {TYPE_2__* back; TYPE_3__* env; TYPE_4__* ctx; scalar_t__ is_bg_thread; } ;
struct edns_data {int dummy; } ;
struct ctx_query {struct libworker* w; void* msg_security; } ;
struct TYPE_10__ {TYPE_1__* env; int /*<<< orphan*/  local_zones; int /*<<< orphan*/  cfglock; } ;
struct TYPE_9__ {int /*<<< orphan*/  mesh; int /*<<< orphan*/  scratch; } ;
struct TYPE_8__ {int /*<<< orphan*/ * udp_buff; } ;
struct TYPE_7__ {scalar_t__ auth_zones; } ;

/* Variables and functions */
 scalar_t__ BIT_RD ; 
 int /*<<< orphan*/  UB_NOERROR ; 
 int /*<<< orphan*/  UB_NOMEM ; 
 int /*<<< orphan*/  UB_SYNTAX ; 
 int /*<<< orphan*/  add_bg_result (struct libworker*,struct ctx_query*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ auth_zones_answer (scalar_t__,TYPE_3__*,struct query_info*,struct edns_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ctx_query* context_deserialize_new_query (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ctx_query* context_lookup_new_query (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libworker_bg_done_cb ; 
 scalar_t__ local_zones_answer (int /*<<< orphan*/ ,TYPE_3__*,struct query_info*,struct edns_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  mesh_new_callback (int /*<<< orphan*/ ,struct query_info*,scalar_t__,struct edns_data*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct ctx_query*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 
 void* sec_status_insecure ; 
 int /*<<< orphan*/  setup_qinfo_edns (struct libworker*,struct ctx_query*,struct query_info*,struct edns_data*) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static void
handle_newq(struct libworker* w, uint8_t* buf, uint32_t len)
{
	uint16_t qflags, qid;
	struct query_info qinfo;
	struct edns_data edns;
	struct ctx_query* q;
	if(w->is_bg_thread) {
		lock_basic_lock(&w->ctx->cfglock);
		q = context_lookup_new_query(w->ctx, buf, len);
		lock_basic_unlock(&w->ctx->cfglock);
	} else {
		q = context_deserialize_new_query(w->ctx, buf, len);
	}
	free(buf);
	if(!q) {
		log_err("failed to deserialize newq");
		return;
	}
	if(!setup_qinfo_edns(w, q, &qinfo, &edns)) {
		add_bg_result(w, q, NULL, UB_SYNTAX, NULL, 0);
		return;
	}
	qid = 0;
	qflags = BIT_RD;
	/* see if there is a fixed answer */
	sldns_buffer_write_u16_at(w->back->udp_buff, 0, qid);
	sldns_buffer_write_u16_at(w->back->udp_buff, 2, qflags);
	if(local_zones_answer(w->ctx->local_zones, w->env, &qinfo, &edns, 
		w->back->udp_buff, w->env->scratch, NULL, NULL, 0, NULL, 0,
		NULL, 0, NULL, 0, NULL)) {
		regional_free_all(w->env->scratch);
		q->msg_security = sec_status_insecure;
		add_bg_result(w, q, w->back->udp_buff, UB_NOERROR, NULL, 0);
		free(qinfo.qname);
		return;
	}
	if(w->ctx->env->auth_zones && auth_zones_answer(w->ctx->env->auth_zones,
		w->env, &qinfo, &edns, NULL, w->back->udp_buff, w->env->scratch)) {
		regional_free_all(w->env->scratch);
		q->msg_security = sec_status_insecure;
		add_bg_result(w, q, w->back->udp_buff, UB_NOERROR, NULL, 0);
		free(qinfo.qname);
		return;
	}
	q->w = w;
	/* process new query */
	if(!mesh_new_callback(w->env->mesh, &qinfo, qflags, &edns, 
		w->back->udp_buff, qid, libworker_bg_done_cb, q)) {
		add_bg_result(w, q, NULL, UB_NOMEM, NULL, 0);
	}
	free(qinfo.qname);
}