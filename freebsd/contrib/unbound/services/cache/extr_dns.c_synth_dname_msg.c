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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct TYPE_6__ {struct packed_rrset_data* data; int /*<<< orphan*/  hash; struct ub_packed_rrset_key* key; } ;
struct TYPE_5__ {size_t dname_len; int /*<<< orphan*/  dname; scalar_t__ flags; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_3__ entry; TYPE_2__ rk; } ;
struct regional {int dummy; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/  qname; } ;
struct packed_rrset_data {scalar_t__ ttl; int security; int count; size_t* rr_len; scalar_t__* rr_ttl; int /*<<< orphan*/ ** rr_data; int /*<<< orphan*/  trust; scalar_t__ rrsig_count; } ;
struct dns_msg {TYPE_1__* rep; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;
struct TYPE_4__ {int qdcount; scalar_t__ ttl; int an_numrrsets; int rrset_count; void* serve_expired_ttl; void* prefetch_ttl; struct ub_packed_rrset_key** rrsets; int /*<<< orphan*/  flags; scalar_t__ ar_numrrsets; scalar_t__ ns_numrrsets; int /*<<< orphan*/  security; scalar_t__ authoritative; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_QR ; 
 size_t LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_RCODE_YXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_CNAME ; 
 void* PREFETCH_TTL_CALC (scalar_t__) ; 
 void* SERVE_EXPIRED_TTL ; 
 struct dns_msg* gen_dns_msg (struct regional*,struct query_info*,int) ; 
 int /*<<< orphan*/  get_cname_target (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,scalar_t__) ; 
 int /*<<< orphan*/  packed_rrset_ptr_fixup (struct packed_rrset_data*) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regional_alloc_zero (struct regional*,int) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  rrset_trust_ans_noAA ; 
 int /*<<< orphan*/  sec_status_unchecked ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct dns_msg*
synth_dname_msg(struct ub_packed_rrset_key* rrset, struct regional* region, 
	time_t now, struct query_info* q, enum sec_status* sec_status)
{
	struct dns_msg* msg;
	struct ub_packed_rrset_key* ck;
	struct packed_rrset_data* newd, *d = (struct packed_rrset_data*)
		rrset->entry.data;
	uint8_t* newname, *dtarg = NULL;
	size_t newlen, dtarglen;
	if(now > d->ttl)
		return NULL;
	/* only allow validated (with DNSSEC) DNAMEs used from cache 
	 * for insecure DNAMEs, query again. */
	*sec_status = d->security;
	/* return sec status, so the status of the CNAME can be checked
	 * by the calling routine. */
	msg = gen_dns_msg(region, q, 2); /* DNAME + CNAME RRset */
	if(!msg)
		return NULL;
	msg->rep->flags = BIT_QR; /* reply, no AA, no error */
        msg->rep->authoritative = 0; /* reply stored in cache can't be authoritative */
	msg->rep->qdcount = 1;
	msg->rep->ttl = d->ttl - now;
	msg->rep->prefetch_ttl = PREFETCH_TTL_CALC(msg->rep->ttl);
	msg->rep->serve_expired_ttl = msg->rep->ttl + SERVE_EXPIRED_TTL;
	msg->rep->security = sec_status_unchecked;
	msg->rep->an_numrrsets = 1;
	msg->rep->ns_numrrsets = 0;
	msg->rep->ar_numrrsets = 0;
	msg->rep->rrset_count = 1;
	msg->rep->rrsets[0] = packed_rrset_copy_region(rrset, region, now);
	if(!msg->rep->rrsets[0]) /* copy DNAME */
		return NULL;
	/* synth CNAME rrset */
	get_cname_target(rrset, &dtarg, &dtarglen);
	if(!dtarg)
		return NULL;
	newlen = q->qname_len + dtarglen - rrset->rk.dname_len;
	if(newlen > LDNS_MAX_DOMAINLEN) {
		msg->rep->flags |= LDNS_RCODE_YXDOMAIN;
		return msg;
	}
	newname = (uint8_t*)regional_alloc(region, newlen);
	if(!newname)
		return NULL;
	/* new name is concatenation of qname front (without DNAME owner)
	 * and DNAME target name */
	memcpy(newname, q->qname, q->qname_len-rrset->rk.dname_len);
	memmove(newname+(q->qname_len-rrset->rk.dname_len), dtarg, dtarglen);
	/* create rest of CNAME rrset */
	ck = (struct ub_packed_rrset_key*)regional_alloc(region, 
		sizeof(struct ub_packed_rrset_key));
	if(!ck)
		return NULL;
	memset(&ck->entry, 0, sizeof(ck->entry));
	msg->rep->rrsets[1] = ck;
	ck->entry.key = ck;
	ck->rk.type = htons(LDNS_RR_TYPE_CNAME);
	ck->rk.rrset_class = rrset->rk.rrset_class;
	ck->rk.flags = 0;
	ck->rk.dname = regional_alloc_init(region, q->qname, q->qname_len);
	if(!ck->rk.dname)
		return NULL;
	ck->rk.dname_len = q->qname_len;
	ck->entry.hash = rrset_key_hash(&ck->rk);
	newd = (struct packed_rrset_data*)regional_alloc_zero(region,
		sizeof(struct packed_rrset_data) + sizeof(size_t) + 
		sizeof(uint8_t*) + sizeof(time_t) + sizeof(uint16_t) 
		+ newlen);
	if(!newd)
		return NULL;
	ck->entry.data = newd;
	newd->ttl = 0; /* 0 for synthesized CNAME TTL */
	newd->count = 1;
	newd->rrsig_count = 0;
	newd->trust = rrset_trust_ans_noAA;
	newd->rr_len = (size_t*)((uint8_t*)newd + 
		sizeof(struct packed_rrset_data));
	newd->rr_len[0] = newlen + sizeof(uint16_t);
	packed_rrset_ptr_fixup(newd);
	newd->rr_ttl[0] = newd->ttl;
	msg->rep->ttl = newd->ttl;
	msg->rep->prefetch_ttl = PREFETCH_TTL_CALC(newd->ttl);
	msg->rep->serve_expired_ttl = newd->ttl + SERVE_EXPIRED_TTL;
	sldns_write_uint16(newd->rr_data[0], newlen);
	memmove(newd->rr_data[0] + sizeof(uint16_t), newname, newlen);
	msg->rep->an_numrrsets ++;
	msg->rep->rrset_count ++;
	return msg;
}