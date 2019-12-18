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
typedef  scalar_t__ uint16_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct reply_info {int qdcount; int an_numrrsets; int ns_numrrsets; int rrset_count; struct ub_packed_rrset_key** rrsets; scalar_t__ flags; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct module_env {int dummy; } ;
struct edns_data {int bits; scalar_t__ ext_rcode; scalar_t__ udp_size; int /*<<< orphan*/  edns_version; } ;
struct comm_reply {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  rep ;

/* Variables and functions */
 int BIT_AA ; 
 int BIT_QR ; 
 int BIT_RA ; 
 scalar_t__ EDNS_ADVERTISED_SIZE ; 
 int /*<<< orphan*/  EDNS_ADVERTISED_VERSION ; 
 int EDNS_DO ; 
 int LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  error_encode (int /*<<< orphan*/ *,int,struct query_info*,scalar_t__,int /*<<< orphan*/ ,struct edns_data*) ; 
 int /*<<< orphan*/  inplace_cb_reply_local_call (struct module_env*,struct query_info*,int /*<<< orphan*/ *,struct reply_info*,int,struct edns_data*,struct comm_reply*,struct regional*) ; 
 int /*<<< orphan*/  memset (struct reply_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reply_info_answer_encode (struct query_info*,struct reply_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*,scalar_t__,struct edns_data*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read_u16_at (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
local_encode(struct query_info* qinfo, struct module_env* env,
	struct edns_data* edns, struct comm_reply* repinfo, sldns_buffer* buf,
	struct regional* temp, struct ub_packed_rrset_key* rrset, int ansec,
	int rcode)
{
	struct reply_info rep;
	uint16_t udpsize;
	/* make answer with time=0 for fixed TTL values */
	memset(&rep, 0, sizeof(rep));
	rep.flags = (uint16_t)((BIT_QR | BIT_AA | BIT_RA) | rcode);
	rep.qdcount = 1;
	if(ansec)
		rep.an_numrrsets = 1;
	else	rep.ns_numrrsets = 1;
	rep.rrset_count = 1;
	rep.rrsets = &rrset;
	udpsize = edns->udp_size;
	edns->edns_version = EDNS_ADVERTISED_VERSION;
	edns->udp_size = EDNS_ADVERTISED_SIZE;
	edns->ext_rcode = 0;
	edns->bits &= EDNS_DO;
	if(!inplace_cb_reply_local_call(env, qinfo, NULL, &rep, rcode, edns,
		repinfo, temp) || !reply_info_answer_encode(qinfo, &rep,
		*(uint16_t*)sldns_buffer_begin(buf), sldns_buffer_read_u16_at(buf, 2),
		buf, 0, 0, temp, udpsize, edns, (int)(edns->bits&EDNS_DO), 0)) {
		error_encode(buf, (LDNS_RCODE_SERVFAIL|BIT_AA), qinfo,
			*(uint16_t*)sldns_buffer_begin(buf),
			sldns_buffer_read_u16_at(buf, 2), edns);
	}
	return 1;
}