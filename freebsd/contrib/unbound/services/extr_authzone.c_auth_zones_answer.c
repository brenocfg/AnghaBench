#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sldns_buffer {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {scalar_t__ qtype; size_t qname_len; int /*<<< orphan*/  qclass; int /*<<< orphan*/ * qname; } ;
struct module_env {int dummy; } ;
struct edns_data {int dummy; } ;
struct dns_msg {int dummy; } ;
struct comm_reply {int dummy; } ;
struct auth_zones {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_query_down; int /*<<< orphan*/  have_downstream; } ;
struct auth_zone {int /*<<< orphan*/  lock; scalar_t__ fallback_enabled; scalar_t__ zone_expired; int /*<<< orphan*/  for_downstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  auth_answer_encode (struct query_info*,struct module_env*,struct edns_data*,struct comm_reply*,struct sldns_buffer*,struct regional*,struct dns_msg*) ; 
 int /*<<< orphan*/  auth_error_encode (struct query_info*,struct module_env*,struct edns_data*,struct comm_reply*,struct sldns_buffer*,struct regional*,int /*<<< orphan*/ ) ; 
 int auth_zone_generate_answer (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg**,int*) ; 
 struct auth_zone* auth_zones_find_zone (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 

int auth_zones_answer(struct auth_zones* az, struct module_env* env,
	struct query_info* qinfo, struct edns_data* edns,
	struct comm_reply* repinfo, struct sldns_buffer* buf, struct regional* temp)
{
	struct dns_msg* msg = NULL;
	struct auth_zone* z;
	int r;
	int fallback = 0;

	lock_rw_rdlock(&az->lock);
	if(!az->have_downstream) {
		/* no downstream auth zones */
		lock_rw_unlock(&az->lock);
		return 0;
	}
	if(qinfo->qtype == LDNS_RR_TYPE_DS) {
		uint8_t* delname = qinfo->qname;
		size_t delnamelen = qinfo->qname_len;
		dname_remove_label(&delname, &delnamelen);
		z = auth_zones_find_zone(az, delname, delnamelen,
			qinfo->qclass);
	} else {
		z = auth_zones_find_zone(az, qinfo->qname, qinfo->qname_len,
			qinfo->qclass);
	}
	if(!z) {
		/* no zone above it */
		lock_rw_unlock(&az->lock);
		return 0;
	}
	lock_rw_rdlock(&z->lock);
	lock_rw_unlock(&az->lock);
	if(!z->for_downstream) {
		lock_rw_unlock(&z->lock);
		return 0;
	}
	if(z->zone_expired) {
		if(z->fallback_enabled) {
			lock_rw_unlock(&z->lock);
			return 0;
		}
		lock_rw_unlock(&z->lock);
		lock_rw_wrlock(&az->lock);
		az->num_query_down++;
		lock_rw_unlock(&az->lock);
		auth_error_encode(qinfo, env, edns, repinfo, buf, temp,
			LDNS_RCODE_SERVFAIL);
		return 1;
	}

	/* answer it from zone z */
	r = auth_zone_generate_answer(z, qinfo, temp, &msg, &fallback);
	lock_rw_unlock(&z->lock);
	if(!r && fallback) {
		/* fallback to regular answering (recursive) */
		return 0;
	}
	lock_rw_wrlock(&az->lock);
	az->num_query_down++;
	lock_rw_unlock(&az->lock);

	/* encode answer */
	if(!r)
		auth_error_encode(qinfo, env, edns, repinfo, buf, temp,
			LDNS_RCODE_SERVFAIL);
	else	auth_answer_encode(qinfo, env, edns, repinfo, buf, temp, msg);

	return 1;
}