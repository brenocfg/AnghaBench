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
struct rrset_parse {scalar_t__ type; scalar_t__ section; struct rrset_parse* rrset_all_next; int /*<<< orphan*/  dname; } ;
struct query_info {int /*<<< orphan*/  qname; } ;
struct msg_parse {scalar_t__ an_rrsets; int /*<<< orphan*/  flags; struct rrset_parse* rrset_first; } ;
struct module_env {TYPE_1__* cfg; } ;
struct iter_env {int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  harden_glue; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_SECTION_ADDITIONAL ; 
 scalar_t__ LDNS_SECTION_ANSWER ; 
 scalar_t__ LDNS_SECTION_AUTHORITY ; 
 scalar_t__ dname_pkt_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ has_additional (scalar_t__) ; 
 scalar_t__ pkt_strict_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pkt_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ priv_rrset_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rrset_parse*) ; 
 int /*<<< orphan*/  remove_rrset (char*,int /*<<< orphan*/ *,struct msg_parse*,struct rrset_parse*,struct rrset_parse**) ; 
 scalar_t__ sanitize_nsec_is_overreach (struct rrset_parse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soa_in_auth (struct msg_parse*) ; 
 int /*<<< orphan*/  store_rrset (int /*<<< orphan*/ *,struct msg_parse*,struct module_env*,struct rrset_parse*) ; 
 scalar_t__ sub_of_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scrub_sanitize(sldns_buffer* pkt, struct msg_parse* msg, 
	struct query_info* qinfo, uint8_t* zonename, struct module_env* env,
	struct iter_env* ie)
{
	int del_addi = 0; /* if additional-holding rrsets are deleted, we
		do not trust the normalized additional-A-AAAA any more */
	struct rrset_parse* rrset, *prev;
	prev = NULL;
	rrset = msg->rrset_first;

	/* the first DNAME is allowed to stay. It needs checking before
	 * it can be used from the cache. After normalization, an initial 
	 * DNAME will have a correctly synthesized CNAME after it. */
	if(rrset && rrset->type == LDNS_RR_TYPE_DNAME && 
		rrset->section == LDNS_SECTION_ANSWER &&
		pkt_strict_sub(pkt, qinfo->qname, rrset->dname) &&
		pkt_sub(pkt, rrset->dname, zonename)) {
		prev = rrset; /* DNAME allowed to stay in answer section */
		rrset = rrset->rrset_all_next;
	}
	
	/* remove all records from the answer section that are 
	 * not the same domain name as the query domain name.
	 * The answer section should contain rrsets with the same name
	 * as the question. For DNAMEs a CNAME has been synthesized.
	 * Wildcards have the query name in answer section.
	 * ANY queries get query name in answer section.
	 * Remainders of CNAME chains are cut off and resolved by iterator. */
	while(rrset && rrset->section == LDNS_SECTION_ANSWER) {
		if(dname_pkt_compare(pkt, qinfo->qname, rrset->dname) != 0) {
			if(has_additional(rrset->type)) del_addi = 1;
			remove_rrset("sanitize: removing extraneous answer "
				"RRset:", pkt, msg, prev, &rrset);
			continue;
		}
		prev = rrset;
		rrset = rrset->rrset_all_next;
	}

	/* At this point, we brutally remove ALL rrsets that aren't 
	 * children of the originating zone. The idea here is that, 
	 * as far as we know, the server that we contacted is ONLY 
	 * authoritative for the originating zone. It, of course, MAY 
	 * be authoritative for any other zones, and of course, MAY 
	 * NOT be authoritative for some subdomains of the originating 
	 * zone. */
	prev = NULL;
	rrset = msg->rrset_first;
	while(rrset) {

		/* remove private addresses */
		if( (rrset->type == LDNS_RR_TYPE_A || 
			rrset->type == LDNS_RR_TYPE_AAAA)) {

			/* do not set servfail since this leads to too
			 * many drops of other people using rfc1918 space */
			/* also do not remove entire rrset, unless all records
			 * in it are bad */
			if(priv_rrset_bad(ie->priv, pkt, rrset)) {
				remove_rrset(NULL, pkt, msg, prev, &rrset);
				continue;
			}
		}
		
		/* skip DNAME records -- they will always be followed by a 
		 * synthesized CNAME, which will be relevant.
		 * FIXME: should this do something differently with DNAME 
		 * rrsets NOT in Section.ANSWER? */
		/* But since DNAME records are also subdomains of the zone,
		 * same check can be used */

		if(!pkt_sub(pkt, rrset->dname, zonename)) {
			if(msg->an_rrsets == 0 && 
				rrset->type == LDNS_RR_TYPE_NS && 
				rrset->section == LDNS_SECTION_AUTHORITY &&
				FLAGS_GET_RCODE(msg->flags) == 
				LDNS_RCODE_NOERROR && !soa_in_auth(msg) &&
				sub_of_pkt(pkt, zonename, rrset->dname)) {
				/* noerror, nodata and this NS rrset is above
				 * the zone. This is LAME! 
				 * Leave in the NS for lame classification. */
				/* remove everything from the additional
				 * (we dont want its glue that was approved
				 * during the normalize action) */
				del_addi = 1;
			} else if(!env->cfg->harden_glue && (
				rrset->type == LDNS_RR_TYPE_A ||
				rrset->type == LDNS_RR_TYPE_AAAA)) {
				/* store in cache! Since it is relevant
				 * (from normalize) it will be picked up 
				 * from the cache to be used later */
				store_rrset(pkt, msg, env, rrset);
				remove_rrset("sanitize: storing potential "
				"poison RRset:", pkt, msg, prev, &rrset);
				continue;
			} else {
				if(has_additional(rrset->type)) del_addi = 1;
				remove_rrset("sanitize: removing potential "
				"poison RRset:", pkt, msg, prev, &rrset);
				continue;
			}
		}
		if(del_addi && rrset->section == LDNS_SECTION_ADDITIONAL) {
			remove_rrset("sanitize: removing potential "
			"poison reference RRset:", pkt, msg, prev, &rrset);
			continue;
		}
		/* check if right hand side of NSEC is within zone */
		if(rrset->type == LDNS_RR_TYPE_NSEC &&
			sanitize_nsec_is_overreach(rrset, zonename)) {
			remove_rrset("sanitize: removing overreaching NSEC "
				"RRset:", pkt, msg, prev, &rrset);
			continue;
		}
		prev = rrset;
		rrset = rrset->rrset_all_next;
	}
	return 1;
}