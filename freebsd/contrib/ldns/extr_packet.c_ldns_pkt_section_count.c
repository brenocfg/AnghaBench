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
typedef  int ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
#define  LDNS_SECTION_ADDITIONAL 133 
#define  LDNS_SECTION_ANSWER 132 
#define  LDNS_SECTION_ANY 131 
#define  LDNS_SECTION_ANY_NOQUESTION 130 
#define  LDNS_SECTION_AUTHORITY 129 
#define  LDNS_SECTION_QUESTION 128 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_arcount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_nscount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_qdcount (int /*<<< orphan*/  const*) ; 

uint16_t
ldns_pkt_section_count(const ldns_pkt *packet, ldns_pkt_section s)
{
	switch(s) {
	case LDNS_SECTION_QUESTION:
		return ldns_pkt_qdcount(packet);
	case LDNS_SECTION_ANSWER:
		return ldns_pkt_ancount(packet);
	case LDNS_SECTION_AUTHORITY:
		return ldns_pkt_nscount(packet);
	case LDNS_SECTION_ADDITIONAL:
		return ldns_pkt_arcount(packet);
	case LDNS_SECTION_ANY:
		return ldns_pkt_qdcount(packet) +
			ldns_pkt_ancount(packet) +
			ldns_pkt_nscount(packet) +
			ldns_pkt_arcount(packet);
	case LDNS_SECTION_ANY_NOQUESTION:
		return ldns_pkt_ancount(packet) +
			ldns_pkt_nscount(packet) +
			ldns_pkt_arcount(packet);
	default:
		return 0;
	}
}