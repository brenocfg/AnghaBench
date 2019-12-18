#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct ub_ctx {TYPE_1__* env; int /*<<< orphan*/  local_zones; struct libworker* event_worker; } ;
struct query_info {int /*<<< orphan*/  qname; } ;
struct libworker {TYPE_2__* back; TYPE_3__* env; } ;
struct edns_data {int dummy; } ;
struct ctx_query {int querynum; struct libworker* w; } ;
struct TYPE_7__ {int /*<<< orphan*/  mesh; int /*<<< orphan*/  scratch; } ;
struct TYPE_6__ {int /*<<< orphan*/  udp_buff; } ;
struct TYPE_5__ {scalar_t__ auth_zones; } ;

/* Variables and functions */
 scalar_t__ BIT_RD ; 
 int /*<<< orphan*/  LDNS_RCODE_NOERROR ; 
 int UB_INITFAIL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_SYNTAX ; 
 scalar_t__ auth_zones_answer (scalar_t__,TYPE_3__*,struct query_info*,struct edns_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libworker_event_done_cb (struct ctx_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ local_zones_answer (int /*<<< orphan*/ ,TYPE_3__*,struct query_info*,struct edns_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_new_callback (int /*<<< orphan*/ ,struct query_info*,scalar_t__,struct edns_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  (*) (struct ctx_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ),struct ctx_query*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_status_insecure ; 
 int /*<<< orphan*/  setup_qinfo_edns (struct libworker*,struct ctx_query*,struct query_info*,struct edns_data*) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ ,int,scalar_t__) ; 

int libworker_attach_mesh(struct ub_ctx* ctx, struct ctx_query* q,
	int* async_id)
{
	struct libworker* w = ctx->event_worker;
	uint16_t qflags, qid;
	struct query_info qinfo;
	struct edns_data edns;
	if(!w)
		return UB_INITFAIL;
	if(!setup_qinfo_edns(w, q, &qinfo, &edns))
		return UB_SYNTAX;
	qid = 0;
	qflags = BIT_RD;
	q->w = w;
	/* see if there is a fixed answer */
	sldns_buffer_write_u16_at(w->back->udp_buff, 0, qid);
	sldns_buffer_write_u16_at(w->back->udp_buff, 2, qflags);
	if(local_zones_answer(ctx->local_zones, w->env, &qinfo, &edns, 
		w->back->udp_buff, w->env->scratch, NULL, NULL, 0, NULL, 0,
		NULL, 0, NULL, 0, NULL)) {
		regional_free_all(w->env->scratch);
		free(qinfo.qname);
		libworker_event_done_cb(q, LDNS_RCODE_NOERROR,
			w->back->udp_buff, sec_status_insecure, NULL, 0);
		return UB_NOERROR;
	}
	if(ctx->env->auth_zones && auth_zones_answer(ctx->env->auth_zones,
		w->env, &qinfo, &edns, NULL, w->back->udp_buff, w->env->scratch)) {
		regional_free_all(w->env->scratch);
		free(qinfo.qname);
		libworker_event_done_cb(q, LDNS_RCODE_NOERROR,
			w->back->udp_buff, sec_status_insecure, NULL, 0);
		return UB_NOERROR;
	}
	/* process new query */
	if(async_id)
		*async_id = q->querynum;
	if(!mesh_new_callback(w->env->mesh, &qinfo, qflags, &edns, 
		w->back->udp_buff, qid, libworker_event_done_cb, q)) {
		free(qinfo.qname);
		return UB_NOMEM;
	}
	free(qinfo.qname);
	return UB_NOERROR;
}