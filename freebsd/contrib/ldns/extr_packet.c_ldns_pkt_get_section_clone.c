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
 int /*<<< orphan*/ * ldns_pkt_all (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_pkt_all_noquestion (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_question (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_list_clone (int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_pkt_get_section_clone(const ldns_pkt *packet, ldns_pkt_section s)
{
	switch(s) {
	case LDNS_SECTION_QUESTION:
		return ldns_rr_list_clone(ldns_pkt_question(packet));
	case LDNS_SECTION_ANSWER:
		return ldns_rr_list_clone(ldns_pkt_answer(packet));
	case LDNS_SECTION_AUTHORITY:
		return ldns_rr_list_clone(ldns_pkt_authority(packet));
	case LDNS_SECTION_ADDITIONAL:
		return ldns_rr_list_clone(ldns_pkt_additional(packet));
	case LDNS_SECTION_ANY:
		/* these are already clones */
		return ldns_pkt_all(packet);
	case LDNS_SECTION_ANY_NOQUESTION:
		return ldns_pkt_all_noquestion(packet);
	default:
		return NULL;
	}
}