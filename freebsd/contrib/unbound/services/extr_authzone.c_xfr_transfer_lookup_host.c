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
typedef  int uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct query_info {int qname_len; int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qclass; int /*<<< orphan*/ * qname; } ;
struct module_env {int /*<<< orphan*/  mesh; int /*<<< orphan*/ * scratch_buffer; } ;
struct edns_data {int edns_present; int udp_size; int /*<<< orphan*/ * opt_list; int /*<<< orphan*/  bits; scalar_t__ edns_version; scalar_t__ ext_rcode; } ;
struct auth_xfer {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; TYPE_1__* task_transfer; int /*<<< orphan*/  dclass; } ;
struct auth_master {int /*<<< orphan*/  host; scalar_t__ allow_notify; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  dname ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_2__ {scalar_t__ lookup_aaaa; struct auth_master* lookup_target; } ;

/* Variables and functions */
 int BIT_RD ; 
 int /*<<< orphan*/  EDNS_DO ; 
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  auth_xfer_transfer_lookup_callback ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ extstrtoaddr (int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_query_info (scalar_t__,char*,struct query_info*) ; 
 int /*<<< orphan*/  mesh_new_callback (int /*<<< orphan*/ ,struct query_info*,int,struct edns_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct auth_xfer*) ; 
 int sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_str2wire_dname_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
xfr_transfer_lookup_host(struct auth_xfer* xfr, struct module_env* env)
{
	struct sockaddr_storage addr;
	socklen_t addrlen = 0;
	struct auth_master* master = xfr->task_transfer->lookup_target;
	struct query_info qinfo;
	uint16_t qflags = BIT_RD;
	uint8_t dname[LDNS_MAX_DOMAINLEN+1];
	struct edns_data edns;
	sldns_buffer* buf = env->scratch_buffer;
	if(!master) return 0;
	if(extstrtoaddr(master->host, &addr, &addrlen)) {
		/* not needed, host is in IP addr format */
		return 0;
	}
	if(master->allow_notify)
		return 0; /* allow-notifies are not transferred from, no
		lookup is needed */

	/* use mesh_new_callback to probe for non-addr hosts,
	 * and then wait for them to be looked up (in cache, or query) */
	qinfo.qname_len = sizeof(dname);
	if(sldns_str2wire_dname_buf(master->host, dname, &qinfo.qname_len)
		!= 0) {
		log_err("cannot parse host name of master %s", master->host);
		return 0;
	}
	qinfo.qname = dname;
	qinfo.qclass = xfr->dclass;
	qinfo.qtype = LDNS_RR_TYPE_A;
	if(xfr->task_transfer->lookup_aaaa)
		qinfo.qtype = LDNS_RR_TYPE_AAAA;
	qinfo.local_alias = NULL;
	if(verbosity >= VERB_ALGO) {
		char buf1[512];
		char buf2[LDNS_MAX_DOMAINLEN+1];
		dname_str(xfr->name, buf2);
		snprintf(buf1, sizeof(buf1), "auth zone %s: master lookup"
			" for task_transfer", buf2);
		log_query_info(VERB_ALGO, buf1, &qinfo);
	}
	edns.edns_present = 1;
	edns.ext_rcode = 0;
	edns.edns_version = 0;
	edns.bits = EDNS_DO;
	edns.opt_list = NULL;
	if(sldns_buffer_capacity(buf) < 65535)
		edns.udp_size = (uint16_t)sldns_buffer_capacity(buf);
	else	edns.udp_size = 65535;

	/* unlock xfr during mesh_new_callback() because the callback can be
	 * called straight away */
	lock_basic_unlock(&xfr->lock);
	if(!mesh_new_callback(env->mesh, &qinfo, qflags, &edns, buf, 0,
		&auth_xfer_transfer_lookup_callback, xfr)) {
		lock_basic_lock(&xfr->lock);
		log_err("out of memory lookup up master %s", master->host);
		return 0;
	}
	lock_basic_lock(&xfr->lock);
	return 1;
}