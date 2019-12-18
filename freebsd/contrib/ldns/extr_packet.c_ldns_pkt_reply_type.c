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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_pkt_type ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_PACKET_ANSWER ; 
 int /*<<< orphan*/  LDNS_PACKET_NODATA ; 
 int /*<<< orphan*/  LDNS_PACKET_NXDOMAIN ; 
 int /*<<< orphan*/  LDNS_PACKET_REFERRAL ; 
 int /*<<< orphan*/  LDNS_PACKET_UNKNOWN ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_arcount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_nscount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 

ldns_pkt_type
ldns_pkt_reply_type(const ldns_pkt *p)
{
	ldns_rr_list *tmp;

	if (!p) {
		return LDNS_PACKET_UNKNOWN;
	}

	if (ldns_pkt_get_rcode(p) == LDNS_RCODE_NXDOMAIN) {
		return LDNS_PACKET_NXDOMAIN;
	}

	if (ldns_pkt_ancount(p) == 0 && ldns_pkt_arcount(p) == 0
			&& ldns_pkt_nscount(p) == 1) {

		/* check for SOA */
		tmp = ldns_pkt_rr_list_by_type(p, LDNS_RR_TYPE_SOA, 
					LDNS_SECTION_AUTHORITY);
		if (tmp) {
			ldns_rr_list_deep_free(tmp);
			return LDNS_PACKET_NODATA;
		} else {
			/* I have no idea ... */
		}
	}

	if (ldns_pkt_ancount(p) == 0 && ldns_pkt_nscount(p) > 0) {
		tmp = ldns_pkt_rr_list_by_type(p, LDNS_RR_TYPE_NS,
		                               LDNS_SECTION_AUTHORITY);
		if (tmp) {
			/* there are nameservers here */
			ldns_rr_list_deep_free(tmp);
			return LDNS_PACKET_REFERRAL;
		} else {
			/* I have no idea */
		}
		ldns_rr_list_deep_free(tmp);
	}
	
	/* if we cannot determine the packet type, we say it's an 
	 * answer...
	 */
	return LDNS_PACKET_ANSWER;
}