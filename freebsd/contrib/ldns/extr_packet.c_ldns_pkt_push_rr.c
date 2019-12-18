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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
#define  LDNS_SECTION_ADDITIONAL 133 
#define  LDNS_SECTION_ANSWER 132 
#define  LDNS_SECTION_ANY 131 
#define  LDNS_SECTION_ANY_NOQUESTION 130 
#define  LDNS_SECTION_AUTHORITY 129 
#define  LDNS_SECTION_QUESTION 128 
 int /*<<< orphan*/  ldns_pkt_additional (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_ancount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_arcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_nscount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_qdcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_question (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_ancount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_arcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_nscount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_qdcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
ldns_pkt_push_rr(ldns_pkt *packet, ldns_pkt_section section, ldns_rr *rr)
{
	switch(section) {
		case LDNS_SECTION_QUESTION:
			if (!ldns_rr_list_push_rr(ldns_pkt_question(packet), rr)) {
				return false;
			}
			ldns_pkt_set_qdcount(packet, ldns_pkt_qdcount(packet) + 1);
			break;
		case LDNS_SECTION_ANSWER:
			if (!ldns_rr_list_push_rr(ldns_pkt_answer(packet), rr)) {
				return false;
			}
			ldns_pkt_set_ancount(packet, ldns_pkt_ancount(packet) + 1);
			break;
		case LDNS_SECTION_AUTHORITY:
			if (!ldns_rr_list_push_rr(ldns_pkt_authority(packet), rr)) {
				return false;
			}
			ldns_pkt_set_nscount(packet, ldns_pkt_nscount(packet) + 1);
			break;
		case LDNS_SECTION_ADDITIONAL:
			if (!ldns_rr_list_push_rr(ldns_pkt_additional(packet), rr)) {
				return false;
			}
			ldns_pkt_set_arcount(packet, ldns_pkt_arcount(packet) + 1);
			break;
		case LDNS_SECTION_ANY:
		case LDNS_SECTION_ANY_NOQUESTION:
			/* shouldn't this error? */
			break;
	}
	return true;
}