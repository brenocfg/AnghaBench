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
typedef  scalar_t__ uint16_t ;
typedef  size_t time_t ;
struct reply_info {scalar_t__ qdcount; int an_numrrsets; int rrset_count; int ns_numrrsets; int ar_numrrsets; int /*<<< orphan*/ * rrsets; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qtype; TYPE_1__* local_alias; } ;
struct compress_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  arep ;
struct TYPE_2__ {int /*<<< orphan*/  rrset; } ;

/* Variables and functions */
 scalar_t__ BIT_AA ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 int /*<<< orphan*/  LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  LDNS_TC_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ MINIMAL_RESPONSES ; 
 int RETVAL_OK ; 
 int RETVAL_TRUNC ; 
 scalar_t__ RRSET_ROUNDROBIN ; 
 int insert_query (struct query_info*,struct compress_tree_node**,int /*<<< orphan*/ *,struct regional*) ; 
 int insert_section (struct reply_info*,int,scalar_t__*,int /*<<< orphan*/ *,int,size_t,struct regional*,struct compress_tree_node**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  memset (struct reply_info*,int /*<<< orphan*/ ,int) ; 
 size_t ntohs (scalar_t__) ; 
 scalar_t__ positive_answer (struct reply_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,int,scalar_t__) ; 
 size_t time (int /*<<< orphan*/ *) ; 

int 
reply_info_encode(struct query_info* qinfo, struct reply_info* rep, 
	uint16_t id, uint16_t flags, sldns_buffer* buffer, time_t timenow, 
	struct regional* region, uint16_t udpsize, int dnssec)
{
	uint16_t ancount=0, nscount=0, arcount=0;
	struct compress_tree_node* tree = 0;
	int r;
	size_t rr_offset; 

	sldns_buffer_clear(buffer);
	if(udpsize < sldns_buffer_limit(buffer))
		sldns_buffer_set_limit(buffer, udpsize);
	if(sldns_buffer_remaining(buffer) < LDNS_HEADER_SIZE)
		return 0;

	sldns_buffer_write(buffer, &id, sizeof(uint16_t));
	sldns_buffer_write_u16(buffer, flags);
	sldns_buffer_write_u16(buffer, rep->qdcount);
	/* set an, ns, ar counts to zero in case of small packets */
	sldns_buffer_write(buffer, "\000\000\000\000\000\000", 6);

	/* insert query section */
	if(rep->qdcount) {
		if((r=insert_query(qinfo, &tree, buffer, region)) != 
			RETVAL_OK) {
			if(r == RETVAL_TRUNC) {
				/* create truncated message */
				sldns_buffer_write_u16_at(buffer, 4, 0);
				LDNS_TC_SET(sldns_buffer_begin(buffer));
				sldns_buffer_flip(buffer);
				return 1;
			}
			return 0;
		}
	}
	/* roundrobin offset. using query id for random number.  With ntohs
	 * for different roundrobins for sequential id client senders. */
	rr_offset = RRSET_ROUNDROBIN?ntohs(id)+(timenow?timenow:time(NULL)):0;

	/* "prepend" any local alias records in the answer section if this
	 * response is supposed to be authoritative.  Currently it should
	 * be a single CNAME record (sanity-checked in worker_handle_request())
	 * but it can be extended if and when we support more variations of
	 * aliases. */
	if(qinfo->local_alias && (flags & BIT_AA)) {
		struct reply_info arep;
		time_t timezero = 0; /* to use the 'authoritative' TTL */
		memset(&arep, 0, sizeof(arep));
		arep.flags = rep->flags;
		arep.an_numrrsets = 1;
		arep.rrset_count = 1;
		arep.rrsets = &qinfo->local_alias->rrset;
		if((r=insert_section(&arep, 1, &ancount, buffer, 0,
			timezero, region, &tree, LDNS_SECTION_ANSWER,
			qinfo->qtype, dnssec, rr_offset)) != RETVAL_OK) {
			if(r == RETVAL_TRUNC) {
				/* create truncated message */
				sldns_buffer_write_u16_at(buffer, 6, ancount);
				LDNS_TC_SET(sldns_buffer_begin(buffer));
				sldns_buffer_flip(buffer);
				return 1;
			}
			return 0;
		}
	}

	/* insert answer section */
	if((r=insert_section(rep, rep->an_numrrsets, &ancount, buffer, 
		0, timenow, region, &tree, LDNS_SECTION_ANSWER, qinfo->qtype, 
		dnssec, rr_offset)) != RETVAL_OK) {
		if(r == RETVAL_TRUNC) {
			/* create truncated message */
			sldns_buffer_write_u16_at(buffer, 6, ancount);
			LDNS_TC_SET(sldns_buffer_begin(buffer));
			sldns_buffer_flip(buffer);
			return 1;
		}
		return 0;
	}
	sldns_buffer_write_u16_at(buffer, 6, ancount);

	/* if response is positive answer, auth/add sections are not required */
	if( ! (MINIMAL_RESPONSES && positive_answer(rep, qinfo->qtype)) ) {
		/* insert auth section */
		if((r=insert_section(rep, rep->ns_numrrsets, &nscount, buffer, 
			rep->an_numrrsets, timenow, region, &tree,
			LDNS_SECTION_AUTHORITY, qinfo->qtype,
			dnssec, rr_offset)) != RETVAL_OK) {
			if(r == RETVAL_TRUNC) {
				/* create truncated message */
				sldns_buffer_write_u16_at(buffer, 8, nscount);
				LDNS_TC_SET(sldns_buffer_begin(buffer));
				sldns_buffer_flip(buffer);
				return 1;
			}
			return 0;
		}
		sldns_buffer_write_u16_at(buffer, 8, nscount);

		/* insert add section */
		if((r=insert_section(rep, rep->ar_numrrsets, &arcount, buffer, 
			rep->an_numrrsets + rep->ns_numrrsets, timenow, region, 
			&tree, LDNS_SECTION_ADDITIONAL, qinfo->qtype, 
			dnssec, rr_offset)) != RETVAL_OK) {
			if(r == RETVAL_TRUNC) {
				/* no need to set TC bit, this is the additional */
				sldns_buffer_write_u16_at(buffer, 10, arcount);
				sldns_buffer_flip(buffer);
				return 1;
			}
			return 0;
		}
		sldns_buffer_write_u16_at(buffer, 10, arcount);
	}
	sldns_buffer_flip(buffer);
	return 1;
}