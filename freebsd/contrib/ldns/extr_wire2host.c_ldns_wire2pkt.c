#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_22__ {scalar_t__ _edns_present; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_OPT ; 
 scalar_t__ LDNS_RR_TYPE_TSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  LDNS_SECTION_QUESTION ; 
 int /*<<< orphan*/  LDNS_STATUS_CHECK_GOTO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_STATUS_INTERNAL_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ LDNS_STATUS_PACKET_OVERFLOW ; 
 scalar_t__ LDNS_STATUS_WIRE_INCOMPLETE_ADDITIONAL ; 
 scalar_t__ LDNS_STATUS_WIRE_INCOMPLETE_ANSWER ; 
 scalar_t__ LDNS_STATUS_WIRE_INCOMPLETE_AUTHORITY ; 
 scalar_t__ LDNS_STATUS_WIRE_INCOMPLETE_QUESTION ; 
 int /*<<< orphan*/  ldns_pkt_additional (TYPE_1__*) ; 
 scalar_t__ ldns_pkt_ancount (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (TYPE_1__*) ; 
 scalar_t__ ldns_pkt_arcount (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_pkt_free (TYPE_1__*) ; 
 TYPE_1__* ldns_pkt_new () ; 
 scalar_t__ ldns_pkt_nscount (TYPE_1__*) ; 
 scalar_t__ ldns_pkt_qdcount (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_pkt_question (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_pkt_set_arcount (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_extended_rcode (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_udp_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_version (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_z (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_size (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  ldns_pkt_set_tsig (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_clone (scalar_t__) ; 
 int /*<<< orphan*/  ldns_read_uint16 (scalar_t__*) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_get_class (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_ttl (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_wire2pkt_hdr (TYPE_1__*,scalar_t__ const*,size_t,size_t*) ; 
 scalar_t__ ldns_wire2rr (int /*<<< orphan*/ **,scalar_t__ const*,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_write_uint32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_error ; 

ldns_status
ldns_wire2pkt(ldns_pkt **packet_p, const uint8_t *wire, size_t max)
{
	size_t pos = 0;
	uint16_t i;
	ldns_rr *rr;
	ldns_pkt *packet = ldns_pkt_new();
	ldns_status status = LDNS_STATUS_OK;
	uint8_t have_edns = 0;

	uint8_t data[4];

	status = ldns_wire2pkt_hdr(packet, wire, max, &pos);
	LDNS_STATUS_CHECK_GOTO(status, status_error);

	for (i = 0; i < ldns_pkt_qdcount(packet); i++) {

		status = ldns_wire2rr(&rr, wire, max, &pos, LDNS_SECTION_QUESTION);
		if (status == LDNS_STATUS_PACKET_OVERFLOW) {
			status = LDNS_STATUS_WIRE_INCOMPLETE_QUESTION;
		}
		LDNS_STATUS_CHECK_GOTO(status, status_error);
		if (!ldns_rr_list_push_rr(ldns_pkt_question(packet), rr)) {
			ldns_pkt_free(packet);
			return LDNS_STATUS_INTERNAL_ERR;
		}
	}
	for (i = 0; i < ldns_pkt_ancount(packet); i++) {
		status = ldns_wire2rr(&rr, wire, max, &pos, LDNS_SECTION_ANSWER);
		if (status == LDNS_STATUS_PACKET_OVERFLOW) {
			status = LDNS_STATUS_WIRE_INCOMPLETE_ANSWER;
		}
		LDNS_STATUS_CHECK_GOTO(status, status_error);
		if (!ldns_rr_list_push_rr(ldns_pkt_answer(packet), rr)) {
			ldns_pkt_free(packet);
			return LDNS_STATUS_INTERNAL_ERR;
		}
	}
	for (i = 0; i < ldns_pkt_nscount(packet); i++) {
		status = ldns_wire2rr(&rr, wire, max, &pos, LDNS_SECTION_AUTHORITY);
		if (status == LDNS_STATUS_PACKET_OVERFLOW) {
			status = LDNS_STATUS_WIRE_INCOMPLETE_AUTHORITY;
		}
		LDNS_STATUS_CHECK_GOTO(status, status_error);
		if (!ldns_rr_list_push_rr(ldns_pkt_authority(packet), rr)) {
			ldns_pkt_free(packet);
			return LDNS_STATUS_INTERNAL_ERR;
		}
	}
	for (i = 0; i < ldns_pkt_arcount(packet); i++) {
		status = ldns_wire2rr(&rr, wire, max, &pos, LDNS_SECTION_ADDITIONAL);
		if (status == LDNS_STATUS_PACKET_OVERFLOW) {
			status = LDNS_STATUS_WIRE_INCOMPLETE_ADDITIONAL;
		}
		LDNS_STATUS_CHECK_GOTO(status, status_error);

		if (ldns_rr_get_type(rr) == LDNS_RR_TYPE_OPT) {
			ldns_pkt_set_edns_udp_size(packet, ldns_rr_get_class(rr));
			ldns_write_uint32(data, ldns_rr_ttl(rr));
			ldns_pkt_set_edns_extended_rcode(packet, data[0]);
			ldns_pkt_set_edns_version(packet, data[1]);
			ldns_pkt_set_edns_z(packet, ldns_read_uint16(&data[2]));
			/* edns might not have rdfs */
			if (ldns_rr_rdf(rr, 0)) {
				ldns_pkt_set_edns_data(packet, ldns_rdf_clone(ldns_rr_rdf(rr, 0)));
			}
			ldns_rr_free(rr);
			have_edns += 1;
		} else if (ldns_rr_get_type(rr) == LDNS_RR_TYPE_TSIG) {
			ldns_pkt_set_tsig(packet, rr);
			ldns_pkt_set_arcount(packet, ldns_pkt_arcount(packet) - 1);
		} else if (!ldns_rr_list_push_rr(ldns_pkt_additional(packet), rr)) {
			ldns_pkt_free(packet);
			return LDNS_STATUS_INTERNAL_ERR;
		}
	}
	ldns_pkt_set_size(packet, max);
	if(have_edns)
		ldns_pkt_set_arcount(packet, ldns_pkt_arcount(packet)
                        - have_edns);
        packet->_edns_present = have_edns;

	*packet_p = packet;
	return status;

status_error:
	ldns_pkt_free(packet);
	return status;
}