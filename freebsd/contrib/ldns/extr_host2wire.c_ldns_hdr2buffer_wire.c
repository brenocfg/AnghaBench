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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ ldns_buffer_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_write_u8 (int /*<<< orphan*/ *,int) ; 
 int ldns_pkt_aa (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_ad (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_arcount (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_cd (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_edns (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_get_opcode (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_get_rcode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_nscount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_qdcount (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_qr (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_ra (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_rd (int /*<<< orphan*/  const*) ; 
 int ldns_pkt_tc (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_tsig (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ldns_status
ldns_hdr2buffer_wire(ldns_buffer *buffer, const ldns_pkt *packet)
{
	uint8_t flags;
	uint16_t arcount;

	if (ldns_buffer_reserve(buffer, 12)) {
		ldns_buffer_write_u16(buffer, ldns_pkt_id(packet));
		
		flags = ldns_pkt_qr(packet) << 7
		        | ldns_pkt_get_opcode(packet) << 3
		        | ldns_pkt_aa(packet) << 2
		        | ldns_pkt_tc(packet) << 1 | ldns_pkt_rd(packet);
		ldns_buffer_write_u8(buffer, flags);
		
		flags = ldns_pkt_ra(packet) << 7
		        /*| ldns_pkt_z(packet) << 6*/
		        | ldns_pkt_ad(packet) << 5
		        | ldns_pkt_cd(packet) << 4
			| ldns_pkt_get_rcode(packet);
		ldns_buffer_write_u8(buffer, flags);
		
		ldns_buffer_write_u16(buffer, ldns_pkt_qdcount(packet));
		ldns_buffer_write_u16(buffer, ldns_pkt_ancount(packet));
		ldns_buffer_write_u16(buffer, ldns_pkt_nscount(packet));
		/* add EDNS0 and TSIG to additional if they are there */
		arcount = ldns_pkt_arcount(packet);
		if (ldns_pkt_tsig(packet)) {
			arcount++;
		}
		if (ldns_pkt_edns(packet)) {
			arcount++;
		}
		ldns_buffer_write_u16(buffer, arcount);
	}
	
	return ldns_buffer_status(buffer);
}