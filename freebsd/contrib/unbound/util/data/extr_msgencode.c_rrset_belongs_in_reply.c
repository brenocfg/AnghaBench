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
typedef  scalar_t__ sldns_pkt_section ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_ANY ; 
#define  LDNS_RR_TYPE_DNSKEY 136 
#define  LDNS_RR_TYPE_DS 135 
#define  LDNS_RR_TYPE_KEY 134 
#define  LDNS_RR_TYPE_NSEC 133 
#define  LDNS_RR_TYPE_NSEC3 132 
#define  LDNS_RR_TYPE_NSEC3PARAMS 131 
#define  LDNS_RR_TYPE_NXT 130 
#define  LDNS_RR_TYPE_RRSIG 129 
#define  LDNS_RR_TYPE_SIG 128 
 scalar_t__ LDNS_SECTION_ANSWER ; 

__attribute__((used)) static int
rrset_belongs_in_reply(sldns_pkt_section s, uint16_t rrtype, uint16_t qtype, 
	int dnssec)
{
	if(dnssec)
		return 1;
	/* skip non DNSSEC types, except if directly queried for */
	if(s == LDNS_SECTION_ANSWER) {
		if(qtype == LDNS_RR_TYPE_ANY || qtype == rrtype)
			return 1;
	}
	/* check DNSSEC-ness */
	switch(rrtype) {
		case LDNS_RR_TYPE_SIG:
		case LDNS_RR_TYPE_KEY:
		case LDNS_RR_TYPE_NXT:
		case LDNS_RR_TYPE_DS:
		case LDNS_RR_TYPE_RRSIG:
		case LDNS_RR_TYPE_NSEC:
		case LDNS_RR_TYPE_DNSKEY:
		case LDNS_RR_TYPE_NSEC3:
		case LDNS_RR_TYPE_NSEC3PARAMS:
			return 0;
	}
	return 1;
}