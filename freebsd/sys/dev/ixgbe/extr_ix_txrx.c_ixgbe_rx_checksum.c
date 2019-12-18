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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  TYPE_1__* if_rxd_info_t ;
struct TYPE_3__ {int iri_csum_flags; int /*<<< orphan*/  iri_csum_data; } ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int CSUM_SCTP_VALID ; 
 int IXGBE_RXDADV_PKTTYPE_ETQF ; 
 int IXGBE_RXDADV_PKTTYPE_SCTP ; 
 int IXGBE_RXD_ERR_IPE ; 
 int IXGBE_RXD_ERR_TCPE ; 
 int IXGBE_RXD_STAT_IPCS ; 
 int IXGBE_RXD_STAT_L4CS ; 
 int TRUE ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
ixgbe_rx_checksum(u32 staterr, if_rxd_info_t ri, u32 ptype)
{
	u16  status = (u16)staterr;
	u8   errors = (u8)(staterr >> 24);
	bool sctp = false;

	if ((ptype & IXGBE_RXDADV_PKTTYPE_ETQF) == 0 &&
	    (ptype & IXGBE_RXDADV_PKTTYPE_SCTP) != 0)
		sctp = TRUE;

	/* IPv4 checksum */
	if (status & IXGBE_RXD_STAT_IPCS) {
		if (!(errors & IXGBE_RXD_ERR_IPE)) {
			/* IP Checksum Good */
			ri->iri_csum_flags = CSUM_IP_CHECKED | CSUM_IP_VALID;
		} else
			ri->iri_csum_flags = 0;
	}
	/* TCP/UDP/SCTP checksum */
	if (status & IXGBE_RXD_STAT_L4CS) {
		u64 type = (CSUM_DATA_VALID | CSUM_PSEUDO_HDR);
#if __FreeBSD_version >= 800000
		if (sctp)
			type = CSUM_SCTP_VALID;
#endif
		if (!(errors & IXGBE_RXD_ERR_TCPE)) {
			ri->iri_csum_flags |= type;
			if (!sctp)
				ri->iri_csum_data = htons(0xffff);
		}
	}
}