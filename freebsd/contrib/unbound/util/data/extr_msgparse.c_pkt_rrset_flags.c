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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  PACKED_RRSET_NSEC_AT_APEX ; 
 int /*<<< orphan*/  PACKED_RRSET_SOA_NEG ; 
 scalar_t__ nsec_at_apex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
pkt_rrset_flags(sldns_buffer* pkt, uint16_t type, sldns_pkt_section sec)
{
	uint32_t f = 0;
	if(type == LDNS_RR_TYPE_NSEC && nsec_at_apex(pkt)) {
		f |= PACKED_RRSET_NSEC_AT_APEX;
	} else if(type == LDNS_RR_TYPE_SOA && sec == LDNS_SECTION_AUTHORITY) {
		f |= PACKED_RRSET_SOA_NEG;
	}
	return f;
}