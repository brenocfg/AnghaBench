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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int LDNS_AA ; 
 int LDNS_AD ; 
 int LDNS_CD ; 
 int LDNS_QR ; 
 int LDNS_RA ; 
 int LDNS_RD ; 
 int LDNS_TC ; 
 int /*<<< orphan*/  ldns_pkt_set_aa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_ad (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_cd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_qr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_ra (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_rd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_tc (int /*<<< orphan*/ *,int) ; 

bool
ldns_pkt_set_flags(ldns_pkt *packet, uint16_t flags)
{
	if (!packet) {
		return false;
	}
	if ((flags & LDNS_QR) == LDNS_QR) {
		ldns_pkt_set_qr(packet, true);
	}
	if ((flags & LDNS_AA) == LDNS_AA) {
		ldns_pkt_set_aa(packet, true);
	}
	if ((flags & LDNS_RD) == LDNS_RD) {
		ldns_pkt_set_rd(packet, true);
	}
	if ((flags & LDNS_TC) == LDNS_TC) {
		ldns_pkt_set_tc(packet, true);
	}
	if ((flags & LDNS_CD) == LDNS_CD) {
		ldns_pkt_set_cd(packet, true);
	}
	if ((flags & LDNS_RA) == LDNS_RA) {
		ldns_pkt_set_ra(packet, true);
	}
	if ((flags & LDNS_AD) == LDNS_AD) {
		ldns_pkt_set_ad(packet, true);
	}
	return true;
}