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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct reply_info {int /*<<< orphan*/ * rrsets; } ;
struct regional {int dummy; } ;
struct compress_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_ANY ; 
 int /*<<< orphan*/  LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int RETVAL_OK ; 
 int packed_rrset_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regional*,int,int,struct compress_tree_node**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
insert_section(struct reply_info* rep, size_t num_rrsets, uint16_t* num_rrs,
	sldns_buffer* pkt, size_t rrsets_before, time_t timenow, 
	struct regional* region, struct compress_tree_node** tree,
	sldns_pkt_section s, uint16_t qtype, int dnssec, size_t rr_offset)
{
	int r;
	size_t i, setstart;
	/* we now allow this function to be called multiple times for the
	 * same section, incrementally updating num_rrs.  The caller is
	 * responsible for initializing it (which is the case in the current
	 * implementation). */

	if(s != LDNS_SECTION_ADDITIONAL) {
		if(s == LDNS_SECTION_ANSWER && qtype == LDNS_RR_TYPE_ANY)
			dnssec = 1; /* include all types in ANY answer */
	  	for(i=0; i<num_rrsets; i++) {
			setstart = sldns_buffer_position(pkt);
			if((r=packed_rrset_encode(rep->rrsets[rrsets_before+i], 
				pkt, num_rrs, timenow, region, 1, 1, tree,
				s, qtype, dnssec, rr_offset))
				!= RETVAL_OK) {
				/* Bad, but if due to size must set TC bit */
				/* trim off the rrset neatly. */
				sldns_buffer_set_position(pkt, setstart);
				return r;
			}
		}
	} else {
	  	for(i=0; i<num_rrsets; i++) {
			setstart = sldns_buffer_position(pkt);
			if((r=packed_rrset_encode(rep->rrsets[rrsets_before+i], 
				pkt, num_rrs, timenow, region, 1, 0, tree,
				s, qtype, dnssec, rr_offset))
				!= RETVAL_OK) {
				sldns_buffer_set_position(pkt, setstart);
				return r;
			}
		}
		if(dnssec)
	  	  for(i=0; i<num_rrsets; i++) {
			setstart = sldns_buffer_position(pkt);
			if((r=packed_rrset_encode(rep->rrsets[rrsets_before+i], 
				pkt, num_rrs, timenow, region, 0, 1, tree,
				s, qtype, dnssec, rr_offset))
				!= RETVAL_OK) {
				sldns_buffer_set_position(pkt, setstart);
				return r;
			}
		  }
	}
	return RETVAL_OK;
}