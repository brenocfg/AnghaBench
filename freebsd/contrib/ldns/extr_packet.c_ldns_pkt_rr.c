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
 int /*<<< orphan*/  ldns_pkt_additional (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_question (int /*<<< orphan*/  const*) ; 
 int ldns_rr_list_contains_rr (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

bool
ldns_pkt_rr(const ldns_pkt *pkt, ldns_pkt_section sec, const ldns_rr *rr)
{
	bool result = false;

	switch (sec) {
	case LDNS_SECTION_QUESTION:
		return ldns_rr_list_contains_rr(ldns_pkt_question(pkt), rr);
	case LDNS_SECTION_ANSWER:
		return ldns_rr_list_contains_rr(ldns_pkt_answer(pkt), rr);
	case LDNS_SECTION_AUTHORITY:
		return ldns_rr_list_contains_rr(ldns_pkt_authority(pkt), rr);
	case LDNS_SECTION_ADDITIONAL:
		return ldns_rr_list_contains_rr(ldns_pkt_additional(pkt), rr);
	case LDNS_SECTION_ANY:
		result = ldns_rr_list_contains_rr(ldns_pkt_question(pkt), rr);
	case LDNS_SECTION_ANY_NOQUESTION:
		result = result
		    || ldns_rr_list_contains_rr(ldns_pkt_answer(pkt), rr)
		    || ldns_rr_list_contains_rr(ldns_pkt_authority(pkt), rr)
		    || ldns_rr_list_contains_rr(ldns_pkt_additional(pkt), rr);
	}

	return result;
}