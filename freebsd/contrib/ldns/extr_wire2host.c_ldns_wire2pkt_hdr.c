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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_AA_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_AD_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_ANCOUNT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_ARCOUNT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_CD_WIRE (int /*<<< orphan*/  const*) ; 
 size_t LDNS_HEADER_SIZE ; 
 int /*<<< orphan*/  LDNS_ID_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_NSCOUNT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_OPCODE_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_QDCOUNT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_QR_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_RA_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_RCODE_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_RD_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_STATUS_WIRE_INCOMPLETE_HEADER ; 
 int /*<<< orphan*/  LDNS_TC_WIRE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_set_aa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ancount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_arcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_cd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_nscount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_opcode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_qdcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_qr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_ra (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_rcode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_rd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_tc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ldns_status
ldns_wire2pkt_hdr(ldns_pkt *packet, const uint8_t *wire, size_t max, size_t *pos)
{
	if (*pos + LDNS_HEADER_SIZE > max) {
		return LDNS_STATUS_WIRE_INCOMPLETE_HEADER;
	} else {
		ldns_pkt_set_id(packet, LDNS_ID_WIRE(wire));
		ldns_pkt_set_qr(packet, LDNS_QR_WIRE(wire));
		ldns_pkt_set_opcode(packet, LDNS_OPCODE_WIRE(wire));
		ldns_pkt_set_aa(packet, LDNS_AA_WIRE(wire));
		ldns_pkt_set_tc(packet, LDNS_TC_WIRE(wire));
		ldns_pkt_set_rd(packet, LDNS_RD_WIRE(wire));
		ldns_pkt_set_ra(packet, LDNS_RA_WIRE(wire));
		ldns_pkt_set_ad(packet, LDNS_AD_WIRE(wire));
		ldns_pkt_set_cd(packet, LDNS_CD_WIRE(wire));
		ldns_pkt_set_rcode(packet, LDNS_RCODE_WIRE(wire));

		ldns_pkt_set_qdcount(packet, LDNS_QDCOUNT(wire));
		ldns_pkt_set_ancount(packet, LDNS_ANCOUNT(wire));
		ldns_pkt_set_nscount(packet, LDNS_NSCOUNT(wire));
		ldns_pkt_set_arcount(packet, LDNS_ARCOUNT(wire));

		*pos += LDNS_HEADER_SIZE;

		return LDNS_STATUS_OK;
	}
}