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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct reply_info {unsigned int flags; scalar_t__ authoritative; } ;
struct regional {int dummy; } ;
struct query_info {scalar_t__ local_alias; } ;
struct edns_data {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 unsigned int BIT_AA ; 
 unsigned int BIT_AD ; 
 unsigned int BIT_CD ; 
 unsigned int BIT_QR ; 
 unsigned int BIT_RD ; 
 scalar_t__ FLAGS_GET_RCODE (unsigned int) ; 
 unsigned int LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  attach_edns_record (int /*<<< orphan*/ *,struct edns_data*) ; 
 unsigned int calc_edns_field_size (struct edns_data*) ; 
 int /*<<< orphan*/  log_assert (unsigned int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  reply_info_encode (struct query_info*,struct reply_info*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regional*,unsigned int,int) ; 
 scalar_t__ sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 

int 
reply_info_answer_encode(struct query_info* qinf, struct reply_info* rep, 
	uint16_t id, uint16_t qflags, sldns_buffer* pkt, time_t timenow,
	int cached, struct regional* region, uint16_t udpsize, 
	struct edns_data* edns, int dnssec, int secure)
{
	uint16_t flags;
	unsigned int attach_edns = 0;

	if(!cached || rep->authoritative) {
		/* original flags, copy RD and CD bits from query. */
		flags = rep->flags | (qflags & (BIT_RD|BIT_CD)); 
	} else {
		/* remove AA bit, copy RD and CD bits from query. */
		flags = (rep->flags & ~BIT_AA) | (qflags & (BIT_RD|BIT_CD)); 
	}
	if(secure && (dnssec || (qflags&BIT_AD)))
		flags |= BIT_AD;
	/* restore AA bit if we have a local alias and the response can be
	 * authoritative.  Also clear AD bit if set as the local data is the
	 * primary answer. */
	if(qinf->local_alias &&
		(FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NOERROR ||
		FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NXDOMAIN)) {
		flags |= BIT_AA;
		flags &= ~BIT_AD;
	}
	log_assert(flags & BIT_QR); /* QR bit must be on in our replies */
	if(udpsize < LDNS_HEADER_SIZE)
		return 0;
	if(sldns_buffer_capacity(pkt) < udpsize)
		udpsize = sldns_buffer_capacity(pkt);
	if(udpsize < LDNS_HEADER_SIZE + calc_edns_field_size(edns)) {
		/* packet too small to contain edns, omit it. */
		attach_edns = 0;
	} else {
		/* reserve space for edns record */
		attach_edns = (unsigned int)calc_edns_field_size(edns);
		udpsize -= attach_edns;
	}

	if(!reply_info_encode(qinf, rep, id, flags, pkt, timenow, region,
		udpsize, dnssec)) {
		log_err("reply encode: out of memory");
		return 0;
	}
	if(attach_edns && sldns_buffer_capacity(pkt) >=
		sldns_buffer_limit(pkt)+attach_edns)
		attach_edns_record(pkt, edns);
	return 1;
}