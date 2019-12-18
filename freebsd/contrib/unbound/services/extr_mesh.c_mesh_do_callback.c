#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct reply_info {scalar_t__ security; } ;
struct TYPE_13__ {int was_ratelimited; TYPE_3__* env; int /*<<< orphan*/  qinfo; int /*<<< orphan*/  region; } ;
struct mesh_state {TYPE_4__ s; } ;
struct TYPE_11__ {size_t udp_size; int bits; scalar_t__ ext_rcode; int /*<<< orphan*/  edns_version; int /*<<< orphan*/ * opt_list; } ;
struct mesh_cb {int /*<<< orphan*/  buf; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,char*,int) ;TYPE_2__ edns; int /*<<< orphan*/  qflags; int /*<<< orphan*/  qid; } ;
struct TYPE_12__ {TYPE_1__* mesh; int /*<<< orphan*/  scratch; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_reply_addrs; } ;

/* Variables and functions */
 size_t EDNS_ADVERTISED_SIZE ; 
 int /*<<< orphan*/  EDNS_ADVERTISED_VERSION ; 
 int EDNS_DO ; 
 int LDNS_RCODE_NOERROR ; 
 int LDNS_RCODE_SERVFAIL ; 
 char* errinf_to_str_bogus (TYPE_4__*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mesh_cb (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,char*,int)) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inplace_cb_reply_call (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,struct reply_info*,int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inplace_cb_reply_servfail_call (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,struct reply_info*,int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_info_answer_encode (int /*<<< orphan*/ *,struct reply_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,TYPE_2__*,int,int) ; 
 scalar_t__ sec_status_bogus ; 
 scalar_t__ sec_status_secure ; 
 scalar_t__ sec_status_secure_sentinel_fail ; 
 scalar_t__ sec_status_unchecked ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

__attribute__((used)) static void
mesh_do_callback(struct mesh_state* m, int rcode, struct reply_info* rep,
	struct mesh_cb* r)
{
	int secure;
	char* reason = NULL;
	int was_ratelimited = m->s.was_ratelimited;
	/* bogus messages are not made into servfail, sec_status passed
	 * to the callback function */
	if(rep && rep->security == sec_status_secure)
		secure = 1;
	else	secure = 0;
	if(!rep && rcode == LDNS_RCODE_NOERROR)
		rcode = LDNS_RCODE_SERVFAIL;
	if(!rcode && (rep->security == sec_status_bogus ||
		rep->security == sec_status_secure_sentinel_fail)) {
		if(!(reason = errinf_to_str_bogus(&m->s)))
			rcode = LDNS_RCODE_SERVFAIL;
	}
	/* send the reply */
	if(rcode) {
		if(rcode == LDNS_RCODE_SERVFAIL) {
			if(!inplace_cb_reply_servfail_call(m->s.env, &m->s.qinfo, &m->s,
				rep, rcode, &r->edns, NULL, m->s.region))
					r->edns.opt_list = NULL;
		} else {
			if(!inplace_cb_reply_call(m->s.env, &m->s.qinfo, &m->s, rep, rcode,
				&r->edns, NULL, m->s.region))
					r->edns.opt_list = NULL;
		}
		fptr_ok(fptr_whitelist_mesh_cb(r->cb));
		(*r->cb)(r->cb_arg, rcode, r->buf, sec_status_unchecked, NULL,
			was_ratelimited);
	} else {
		size_t udp_size = r->edns.udp_size;
		sldns_buffer_clear(r->buf);
		r->edns.edns_version = EDNS_ADVERTISED_VERSION;
		r->edns.udp_size = EDNS_ADVERTISED_SIZE;
		r->edns.ext_rcode = 0;
		r->edns.bits &= EDNS_DO;

		if(!inplace_cb_reply_call(m->s.env, &m->s.qinfo, &m->s, rep,
			LDNS_RCODE_NOERROR, &r->edns, NULL, m->s.region) ||
			!reply_info_answer_encode(&m->s.qinfo, rep, r->qid, 
			r->qflags, r->buf, 0, 1, 
			m->s.env->scratch, udp_size, &r->edns, 
			(int)(r->edns.bits & EDNS_DO), secure)) 
		{
			fptr_ok(fptr_whitelist_mesh_cb(r->cb));
			(*r->cb)(r->cb_arg, LDNS_RCODE_SERVFAIL, r->buf,
				sec_status_unchecked, NULL, 0);
		} else {
			fptr_ok(fptr_whitelist_mesh_cb(r->cb));
			(*r->cb)(r->cb_arg, LDNS_RCODE_NOERROR, r->buf,
				rep->security, reason, was_ratelimited);
		}
	}
	free(reason);
	m->s.env->mesh->num_reply_addrs--;
}