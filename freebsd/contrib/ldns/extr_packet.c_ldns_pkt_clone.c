#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_59__   TYPE_1__ ;

/* Type definitions */
struct TYPE_59__ {void* _additional; void* _authority; void* _answer; void* _question; int /*<<< orphan*/  _edns_present; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_pkt_aa (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_ad (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_additional (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_ancount (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_answerfrom (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_arcount (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_cd (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_edns_data (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_do (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_extended_rcode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_udp_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_version (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_z (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_get_opcode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_get_rcode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_id (TYPE_1__ const*) ; 
 TYPE_1__* ldns_pkt_new () ; 
 int /*<<< orphan*/  ldns_pkt_nscount (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_qdcount (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_qr (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_querytime (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_question (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_ra (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_rd (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_set_aa (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ad (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ancount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_answerfrom (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_arcount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_cd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_do (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_extended_rcode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_udp_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_version (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_z (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_nscount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_opcode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_qdcount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_qr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_querytime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ra (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_rcode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_rd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_tc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_timestamp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_tsig (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_tc (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_timestamp (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_tsig (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_rdf_clone (scalar_t__) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ ) ; 
 void* ldns_rr_list_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (void*) ; 

ldns_pkt *
ldns_pkt_clone(const ldns_pkt *pkt)
{
	ldns_pkt *new_pkt;
	
	if (!pkt) {
		return NULL;
	}
	new_pkt = ldns_pkt_new();

	ldns_pkt_set_id(new_pkt, ldns_pkt_id(pkt));
	ldns_pkt_set_qr(new_pkt, ldns_pkt_qr(pkt));
	ldns_pkt_set_aa(new_pkt, ldns_pkt_aa(pkt));
	ldns_pkt_set_tc(new_pkt, ldns_pkt_tc(pkt));
	ldns_pkt_set_rd(new_pkt, ldns_pkt_rd(pkt));
	ldns_pkt_set_cd(new_pkt, ldns_pkt_cd(pkt));
	ldns_pkt_set_ra(new_pkt, ldns_pkt_ra(pkt));
	ldns_pkt_set_ad(new_pkt, ldns_pkt_ad(pkt));
	ldns_pkt_set_opcode(new_pkt, ldns_pkt_get_opcode(pkt));
	ldns_pkt_set_rcode(new_pkt, ldns_pkt_get_rcode(pkt));
	ldns_pkt_set_qdcount(new_pkt, ldns_pkt_qdcount(pkt));
	ldns_pkt_set_ancount(new_pkt, ldns_pkt_ancount(pkt));
	ldns_pkt_set_nscount(new_pkt, ldns_pkt_nscount(pkt));
	ldns_pkt_set_arcount(new_pkt, ldns_pkt_arcount(pkt));
	if (ldns_pkt_answerfrom(pkt))
		ldns_pkt_set_answerfrom(new_pkt,
			ldns_rdf_clone(ldns_pkt_answerfrom(pkt)));
	ldns_pkt_set_timestamp(new_pkt, ldns_pkt_timestamp(pkt));
	ldns_pkt_set_querytime(new_pkt, ldns_pkt_querytime(pkt));
	ldns_pkt_set_size(new_pkt, ldns_pkt_size(pkt));
	ldns_pkt_set_tsig(new_pkt, ldns_rr_clone(ldns_pkt_tsig(pkt)));
	
	ldns_pkt_set_edns_udp_size(new_pkt, ldns_pkt_edns_udp_size(pkt));
	ldns_pkt_set_edns_extended_rcode(new_pkt, 
		ldns_pkt_edns_extended_rcode(pkt));
	ldns_pkt_set_edns_version(new_pkt, ldns_pkt_edns_version(pkt));
	new_pkt->_edns_present = pkt->_edns_present;
	ldns_pkt_set_edns_z(new_pkt, ldns_pkt_edns_z(pkt));
	if(ldns_pkt_edns_data(pkt))
		ldns_pkt_set_edns_data(new_pkt, 
			ldns_rdf_clone(ldns_pkt_edns_data(pkt)));
	ldns_pkt_set_edns_do(new_pkt, ldns_pkt_edns_do(pkt));

	ldns_rr_list_deep_free(new_pkt->_question);
	ldns_rr_list_deep_free(new_pkt->_answer);
	ldns_rr_list_deep_free(new_pkt->_authority);
	ldns_rr_list_deep_free(new_pkt->_additional);
	new_pkt->_question = ldns_rr_list_clone(ldns_pkt_question(pkt));
	new_pkt->_answer = ldns_rr_list_clone(ldns_pkt_answer(pkt));
	new_pkt->_authority = ldns_rr_list_clone(ldns_pkt_authority(pkt));
	new_pkt->_additional = ldns_rr_list_clone(ldns_pkt_additional(pkt));
	return new_pkt;
}