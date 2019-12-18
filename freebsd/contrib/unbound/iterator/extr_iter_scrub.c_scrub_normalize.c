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
struct rrset_parse {scalar_t__ section; scalar_t__ type; int rr_count; int flags; struct rrset_parse* rrset_all_next; scalar_t__ rrsig_count; int /*<<< orphan*/ * dname; } ;
struct regional {int dummy; } ;
struct query_info {size_t qname_len; scalar_t__ qtype; int /*<<< orphan*/ * qname; } ;
struct msg_parse {int an_rrsets; int rrset_count; struct rrset_parse* rrset_last; struct rrset_parse* rrset_first; scalar_t__ ar_rrsets; scalar_t__ ns_rrsets; scalar_t__ arcount; scalar_t__ nscount; scalar_t__ ancount; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_ANY ; 
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_SECTION_ADDITIONAL ; 
 scalar_t__ LDNS_SECTION_ANSWER ; 
 scalar_t__ LDNS_SECTION_AUTHORITY ; 
 int RRSET_SCRUB_OK ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ dname_pkt_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  mark_additional_rrset (int /*<<< orphan*/ *,struct msg_parse*,struct rrset_parse*) ; 
 scalar_t__ parse_get_cname_target (struct rrset_parse*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ pkt_strict_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_rrset (char*,int /*<<< orphan*/ *,struct msg_parse*,struct rrset_parse*,struct rrset_parse**) ; 
 scalar_t__ soa_in_auth (struct msg_parse*) ; 
 int /*<<< orphan*/  sub_of_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ synth_cname (int /*<<< orphan*/ *,size_t,struct rrset_parse*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 struct rrset_parse* synth_cname_rrset (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,struct regional*,struct msg_parse*,struct rrset_parse*,struct rrset_parse*,struct rrset_parse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
scrub_normalize(sldns_buffer* pkt, struct msg_parse* msg, 
	struct query_info* qinfo, struct regional* region)
{
	uint8_t* sname = qinfo->qname;
	size_t snamelen = qinfo->qname_len;
	struct rrset_parse* rrset, *prev, *nsset=NULL;

	if(FLAGS_GET_RCODE(msg->flags) != LDNS_RCODE_NOERROR &&
		FLAGS_GET_RCODE(msg->flags) != LDNS_RCODE_NXDOMAIN)
		return 1;

	/* For the ANSWER section, remove all "irrelevant" records and add
	 * synthesized CNAMEs from DNAMEs
	 * This will strip out-of-order CNAMEs as well. */

	/* walk through the parse packet rrset list, keep track of previous
	 * for insert and delete ease, and examine every RRset */
	prev = NULL;
	rrset = msg->rrset_first;
	while(rrset && rrset->section == LDNS_SECTION_ANSWER) {
		if(rrset->type == LDNS_RR_TYPE_DNAME && 
			pkt_strict_sub(pkt, sname, rrset->dname)) {
			/* check if next rrset is correct CNAME. else,
			 * synthesize a CNAME */
			struct rrset_parse* nx = rrset->rrset_all_next;
			uint8_t alias[LDNS_MAX_DOMAINLEN+1];
			size_t aliaslen = 0;
			if(rrset->rr_count != 1) {
				verbose(VERB_ALGO, "Found DNAME rrset with "
					"size > 1: %u", 
					(unsigned)rrset->rr_count);
				return 0;
			}
			if(!synth_cname(sname, snamelen, rrset, alias, 
				&aliaslen, pkt)) {
				verbose(VERB_ALGO, "synthesized CNAME "
					"too long");
				return 0;
			}
			if(nx && nx->type == LDNS_RR_TYPE_CNAME && 
			   dname_pkt_compare(pkt, sname, nx->dname) == 0) {
				/* check next cname */
				uint8_t* t = NULL;
				size_t tlen = 0;
				if(!parse_get_cname_target(nx, &t, &tlen))
					return 0;
				if(dname_pkt_compare(pkt, alias, t) == 0) {
					/* it's OK and better capitalized */
					prev = rrset;
					rrset = nx;
					continue;
				}
				/* synth ourselves */
			}
			/* synth a CNAME rrset */
			prev = synth_cname_rrset(&sname, &snamelen, alias, 
				aliaslen, region, msg, rrset, rrset, nx, pkt);
			if(!prev) {
				log_err("out of memory synthesizing CNAME");
				return 0;
			}
			/* FIXME: resolve the conflict between synthesized 
			 * CNAME ttls and the cache. */
			rrset = nx;
			continue;

		}

		/* The only records in the ANSWER section not allowed to */
		if(dname_pkt_compare(pkt, sname, rrset->dname) != 0) {
			remove_rrset("normalize: removing irrelevant RRset:", 
				pkt, msg, prev, &rrset);
			continue;
		}

		/* Follow the CNAME chain. */
		if(rrset->type == LDNS_RR_TYPE_CNAME) {
			struct rrset_parse* nx = rrset->rrset_all_next;
			uint8_t* oldsname = sname;
			/* see if the next one is a DNAME, if so, swap them */
			if(nx && nx->section == LDNS_SECTION_ANSWER &&
				nx->type == LDNS_RR_TYPE_DNAME &&
				nx->rr_count == 1 &&
				pkt_strict_sub(pkt, sname, nx->dname)) {
				/* there is a DNAME after this CNAME, it 
				 * is in the ANSWER section, and the DNAME
				 * applies to the name we cover */
				/* check if the alias of the DNAME equals
				 * this CNAME */
				uint8_t alias[LDNS_MAX_DOMAINLEN+1];
				size_t aliaslen = 0;
				uint8_t* t = NULL;
				size_t tlen = 0;
				if(synth_cname(sname, snamelen, nx, alias,
					&aliaslen, pkt) &&
					parse_get_cname_target(rrset, &t, &tlen) &&
			   		dname_pkt_compare(pkt, alias, t) == 0) {
					/* the synthesized CNAME equals the
					 * current CNAME.  This CNAME is the
					 * one that the DNAME creates, and this
					 * CNAME is better capitalised */
					verbose(VERB_ALGO, "normalize: re-order of DNAME and its CNAME");
					if(prev) prev->rrset_all_next = nx;
					else msg->rrset_first = nx;
					if(nx->rrset_all_next == NULL)
						msg->rrset_last = rrset;
					rrset->rrset_all_next =
						nx->rrset_all_next;
					nx->rrset_all_next = rrset;
					/* prev = nx; unused, enable if there
					 * is other rrset removal code after
					 * this */
				}
			}

			/* move to next name in CNAME chain */
			if(!parse_get_cname_target(rrset, &sname, &snamelen))
				return 0;
			prev = rrset;
			rrset = rrset->rrset_all_next;
			/* in CNAME ANY response, can have data after CNAME */
			if(qinfo->qtype == LDNS_RR_TYPE_ANY) {
				while(rrset && rrset->section ==
					LDNS_SECTION_ANSWER &&
					dname_pkt_compare(pkt, oldsname,
					rrset->dname) == 0) {
					prev = rrset;
					rrset = rrset->rrset_all_next;
				}
			}
			continue;
		}

		/* Otherwise, make sure that the RRset matches the qtype. */
		if(qinfo->qtype != LDNS_RR_TYPE_ANY && 
			qinfo->qtype != rrset->type) {
			remove_rrset("normalize: removing irrelevant RRset:", 
				pkt, msg, prev, &rrset);
			continue;
		}

		/* Mark the additional names from relevant rrset as OK. */
		/* only for RRsets that match the query name, other ones
		 * will be removed by sanitize, so no additional for them */
		if(dname_pkt_compare(pkt, qinfo->qname, rrset->dname) == 0)
			mark_additional_rrset(pkt, msg, rrset);
		
		prev = rrset;
		rrset = rrset->rrset_all_next;
	}

	/* Mark additional names from AUTHORITY */
	while(rrset && rrset->section == LDNS_SECTION_AUTHORITY) {
		if(rrset->type==LDNS_RR_TYPE_DNAME ||
			rrset->type==LDNS_RR_TYPE_CNAME ||
			rrset->type==LDNS_RR_TYPE_A ||
			rrset->type==LDNS_RR_TYPE_AAAA) {
			remove_rrset("normalize: removing irrelevant "
				"RRset:", pkt, msg, prev, &rrset);
			continue;
		}
		/* only one NS set allowed in authority section */
		if(rrset->type==LDNS_RR_TYPE_NS) {
			/* NS set must be pertinent to the query */
			if(!sub_of_pkt(pkt, qinfo->qname, rrset->dname)) {
				remove_rrset("normalize: removing irrelevant "
					"RRset:", pkt, msg, prev, &rrset);
				continue;
			}
			/* we don't want NS sets for NXDOMAIN answers,
			 * because they could contain poisonous contents,
			 * from. eg. fragmentation attacks, inserted after
			 * long RRSIGs in the packet get to the packet
			 * border and such */
			/* also for NODATA answers */
			if(FLAGS_GET_RCODE(msg->flags) == LDNS_RCODE_NXDOMAIN ||
			   (FLAGS_GET_RCODE(msg->flags) == LDNS_RCODE_NOERROR
			    && soa_in_auth(msg) && msg->an_rrsets == 0)) {
				remove_rrset("normalize: removing irrelevant "
					"RRset:", pkt, msg, prev, &rrset);
				continue;
			}
			if(nsset == NULL) {
				nsset = rrset;
			} else {
				remove_rrset("normalize: removing irrelevant "
					"RRset:", pkt, msg, prev, &rrset);
				continue;
			}
		}
		/* if this is type DS and we query for type DS we just got
		 * a referral answer for our type DS query, fix packet */
		if(rrset->type==LDNS_RR_TYPE_DS &&
			qinfo->qtype == LDNS_RR_TYPE_DS &&
			dname_pkt_compare(pkt, qinfo->qname, rrset->dname) == 0) {
			rrset->section = LDNS_SECTION_ANSWER;
			msg->ancount = rrset->rr_count + rrset->rrsig_count;
			msg->nscount = 0;
			msg->arcount = 0;
			msg->an_rrsets = 1;
			msg->ns_rrsets = 0;
			msg->ar_rrsets = 0;
			msg->rrset_count = 1;
			msg->rrset_first = rrset;
			msg->rrset_last = rrset;
			rrset->rrset_all_next = NULL;
			return 1;
		}
		mark_additional_rrset(pkt, msg, rrset);
		prev = rrset;
		rrset = rrset->rrset_all_next;
	}

	/* For each record in the additional section, remove it if it is an
	 * address record and not in the collection of additional names 
	 * found in ANSWER and AUTHORITY. */
	/* These records have not been marked OK previously */
	while(rrset && rrset->section == LDNS_SECTION_ADDITIONAL) {
		/* FIXME: what about other types? */
		if(rrset->type==LDNS_RR_TYPE_A || 
			rrset->type==LDNS_RR_TYPE_AAAA) 
		{
			if((rrset->flags & RRSET_SCRUB_OK)) {
				/* remove flag to clean up flags variable */
				rrset->flags &= ~RRSET_SCRUB_OK;
			} else {
				remove_rrset("normalize: removing irrelevant "
					"RRset:", pkt, msg, prev, &rrset);
				continue;
			}
		}
		if(rrset->type==LDNS_RR_TYPE_DNAME || 
			rrset->type==LDNS_RR_TYPE_CNAME ||
			rrset->type==LDNS_RR_TYPE_NS) {
			remove_rrset("normalize: removing irrelevant "
				"RRset:", pkt, msg, prev, &rrset);
			continue;
		}
		prev = rrset;
		rrset = rrset->rrset_all_next;
	}
	
	return 1;
}