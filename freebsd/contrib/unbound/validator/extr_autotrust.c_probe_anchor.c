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
typedef  int uint16_t ;
struct trust_anchor {int /*<<< orphan*/  lock; TYPE_1__* autr; int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; int /*<<< orphan*/  qtype; int /*<<< orphan*/ * local_alias; } ;
struct module_env {int /*<<< orphan*/  mesh; int /*<<< orphan*/  key_cache; int /*<<< orphan*/  rrset_cache; scalar_t__* now; int /*<<< orphan*/  scratch; int /*<<< orphan*/ * scratch_buffer; } ;
struct edns_data {int edns_present; int udp_size; int /*<<< orphan*/ * opt_list; int /*<<< orphan*/  bits; scalar_t__ edns_version; scalar_t__ ext_rcode; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {scalar_t__ next_probe_time; } ;

/* Variables and functions */
 int BIT_RD ; 
 int /*<<< orphan*/  EDNS_DO ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  key_cache_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,struct query_info*) ; 
 int /*<<< orphan*/  mesh_new_callback (int /*<<< orphan*/ ,struct query_info*,int,struct edns_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct module_env*) ; 
 int /*<<< orphan*/  probe_answer_cb ; 
 int /*<<< orphan*/  regional_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_cache_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
probe_anchor(struct module_env* env, struct trust_anchor* tp)
{
	struct query_info qinfo;
	uint16_t qflags = BIT_RD;
	struct edns_data edns;
	sldns_buffer* buf = env->scratch_buffer;
	qinfo.qname = regional_alloc_init(env->scratch, tp->name, tp->namelen);
	if(!qinfo.qname) {
		log_err("out of memory making 5011 probe");
		return;
	}
	qinfo.qname_len = tp->namelen;
	qinfo.qtype = LDNS_RR_TYPE_DNSKEY;
	qinfo.qclass = tp->dclass;
	qinfo.local_alias = NULL;
	log_query_info(VERB_ALGO, "autotrust probe", &qinfo);
	verbose(VERB_ALGO, "retry probe set in %d seconds", 
		(int)tp->autr->next_probe_time - (int)*env->now);
	edns.edns_present = 1;
	edns.ext_rcode = 0;
	edns.edns_version = 0;
	edns.bits = EDNS_DO;
	edns.opt_list = NULL;
	if(sldns_buffer_capacity(buf) < 65535)
		edns.udp_size = (uint16_t)sldns_buffer_capacity(buf);
	else	edns.udp_size = 65535;

	/* can't hold the lock while mesh_run is processing */
	lock_basic_unlock(&tp->lock);

	/* delete the DNSKEY from rrset and key cache so an active probe
	 * is done. First the rrset so another thread does not use it
	 * to recreate the key entry in a race condition. */
	rrset_cache_remove(env->rrset_cache, qinfo.qname, qinfo.qname_len,
		qinfo.qtype, qinfo.qclass, 0);
	key_cache_remove(env->key_cache, qinfo.qname, qinfo.qname_len, 
		qinfo.qclass);

	if(!mesh_new_callback(env->mesh, &qinfo, qflags, &edns, buf, 0, 
		&probe_answer_cb, env)) {
		log_err("out of memory making 5011 probe");
	}
}