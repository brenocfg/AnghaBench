#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct sldns_buffer {int dummy; } ;
struct reply_info {int /*<<< orphan*/  flags; } ;
struct TYPE_18__ {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; } ;
struct TYPE_14__ {scalar_t__ return_rcode; TYPE_8__* env; scalar_t__ is_drop; TYPE_4__ qinfo; TYPE_3__* respip_action_info; TYPE_1__* return_msg; } ;
struct TYPE_20__ {scalar_t__ count; } ;
struct mesh_state {int replies_sent; TYPE_11__ s; TYPE_6__ super_set; struct mesh_cb* cb_list; struct mesh_reply* reply_list; } ;
struct TYPE_13__ {TYPE_5__* c; } ;
struct mesh_reply {TYPE_10__ query_reply; int /*<<< orphan*/  local_alias; int /*<<< orphan*/  qname; struct mesh_reply* next; } ;
struct mesh_cb {struct mesh_cb* next; } ;
struct TYPE_23__ {struct sldns_buffer* spool_buffer; } ;
struct TYPE_22__ {TYPE_7__* mesh; TYPE_2__* cfg; } ;
struct TYPE_21__ {int /*<<< orphan*/  num_detached_states; int /*<<< orphan*/  num_reply_states; } ;
struct TYPE_19__ {TYPE_9__* tcp_req_info; struct sldns_buffer* buffer; } ;
struct TYPE_17__ {scalar_t__ addrinfo; } ;
struct TYPE_16__ {int /*<<< orphan*/  val_log_squelch; scalar_t__ log_servfail; } ;
struct TYPE_15__ {struct reply_info* rep; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  comm_point_drop_reply (TYPE_10__*) ; 
 char* errinf_to_str_servfail (TYPE_11__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 int /*<<< orphan*/  mesh_do_callback (struct mesh_state*,scalar_t__,struct reply_info*,struct mesh_cb*) ; 
 int /*<<< orphan*/  mesh_send_reply (struct mesh_state*,scalar_t__,struct reply_info*,struct mesh_reply*,struct sldns_buffer*,struct mesh_reply*,struct sldns_buffer*) ; 
 int /*<<< orphan*/  respip_inform_print (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  tcp_req_info_remove_mesh_state (TYPE_9__*,struct mesh_state*) ; 

void mesh_query_done(struct mesh_state* mstate)
{
	struct mesh_reply* r;
	struct mesh_reply* prev = NULL;
	struct sldns_buffer* prev_buffer = NULL;
	struct mesh_cb* c;
	struct reply_info* rep = (mstate->s.return_msg?
		mstate->s.return_msg->rep:NULL);
	if((mstate->s.return_rcode == LDNS_RCODE_SERVFAIL ||
		(rep && FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_SERVFAIL))
		&& mstate->s.env->cfg->log_servfail
		&& !mstate->s.env->cfg->val_log_squelch) {
		char* err = errinf_to_str_servfail(&mstate->s);
		if(err)
			log_err("%s", err);
		free(err);
	}
	for(r = mstate->reply_list; r; r = r->next) {
		/* if a response-ip address block has been stored the
		 *  information should be logged for each client. */
		if(mstate->s.respip_action_info &&
			mstate->s.respip_action_info->addrinfo) {
			respip_inform_print(mstate->s.respip_action_info->addrinfo,
				r->qname, mstate->s.qinfo.qtype,
				mstate->s.qinfo.qclass, r->local_alias,
				&r->query_reply);
		}

		/* if this query is determined to be dropped during the
		 * mesh processing, this is the point to take that action. */
		if(mstate->s.is_drop)
			comm_point_drop_reply(&r->query_reply);
		else {
			struct sldns_buffer* r_buffer = r->query_reply.c->buffer;
			if(r->query_reply.c->tcp_req_info) {
				r_buffer = r->query_reply.c->tcp_req_info->spool_buffer;
				prev_buffer = NULL;
			}
			mesh_send_reply(mstate, mstate->s.return_rcode, rep,
				r, r_buffer, prev, prev_buffer);
			if(r->query_reply.c->tcp_req_info) {
				tcp_req_info_remove_mesh_state(r->query_reply.c->tcp_req_info, mstate);
				r_buffer = NULL;
			}
			prev = r;
			prev_buffer = r_buffer;
		}
	}
	mstate->replies_sent = 1;
	while((c = mstate->cb_list) != NULL) {
		/* take this cb off the list; so that the list can be
		 * changed, eg. by adds from the callback routine */
		if(!mstate->reply_list && mstate->cb_list && !c->next) {
			/* was a reply state, not anymore */
			mstate->s.env->mesh->num_reply_states--;
		}
		mstate->cb_list = c->next;
		if(!mstate->reply_list && !mstate->cb_list &&
			mstate->super_set.count == 0)
			mstate->s.env->mesh->num_detached_states++;
		mesh_do_callback(mstate, mstate->s.return_rcode, rep, c);
	}
}