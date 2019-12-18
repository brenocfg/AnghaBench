#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ ldns_lookup_table ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_opcodes ; 
 scalar_t__ ldns_pkt_aa (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_ad (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_arcount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_cd (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_get_opcode (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_id (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_nscount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_qdcount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_qr (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_ra (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_rd (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_tc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rcodes ; 

ldns_status
ldns_pktheader2buffer_str(ldns_buffer *output, const ldns_pkt *pkt)
{
	ldns_lookup_table *opcode = ldns_lookup_by_id(ldns_opcodes,
			                    (int) ldns_pkt_get_opcode(pkt));
	ldns_lookup_table *rcode = ldns_lookup_by_id(ldns_rcodes,
			                    (int) ldns_pkt_get_rcode(pkt));

	ldns_buffer_printf(output, ";; ->>HEADER<<- ");
	if (opcode) {
		ldns_buffer_printf(output, "opcode: %s, ", opcode->name);
	} else {
		ldns_buffer_printf(output, "opcode: ?? (%u), ",
				ldns_pkt_get_opcode(pkt));
	}
	if (rcode) {
		ldns_buffer_printf(output, "rcode: %s, ", rcode->name);
	} else {
		ldns_buffer_printf(output, "rcode: ?? (%u), ", ldns_pkt_get_rcode(pkt));
	}
	ldns_buffer_printf(output, "id: %d\n", ldns_pkt_id(pkt));
	ldns_buffer_printf(output, ";; flags: ");

	if (ldns_pkt_qr(pkt)) {
		ldns_buffer_printf(output, "qr ");
	}
	if (ldns_pkt_aa(pkt)) {
		ldns_buffer_printf(output, "aa ");
	}
	if (ldns_pkt_tc(pkt)) {
		ldns_buffer_printf(output, "tc ");
	}
	if (ldns_pkt_rd(pkt)) {
		ldns_buffer_printf(output, "rd ");
	}
	if (ldns_pkt_cd(pkt)) {
		ldns_buffer_printf(output, "cd ");
	}
	if (ldns_pkt_ra(pkt)) {
		ldns_buffer_printf(output, "ra ");
	}
	if (ldns_pkt_ad(pkt)) {
		ldns_buffer_printf(output, "ad ");
	}
	ldns_buffer_printf(output, "; ");
	ldns_buffer_printf(output, "QUERY: %u, ", ldns_pkt_qdcount(pkt));
	ldns_buffer_printf(output, "ANSWER: %u, ", ldns_pkt_ancount(pkt));
	ldns_buffer_printf(output, "AUTHORITY: %u, ", ldns_pkt_nscount(pkt));
	ldns_buffer_printf(output, "ADDITIONAL: %u ", ldns_pkt_arcount(pkt));
	return ldns_buffer_status(output);
}