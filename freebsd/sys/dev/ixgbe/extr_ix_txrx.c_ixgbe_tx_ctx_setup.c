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
typedef  int u32 ;
struct ixgbe_adv_tx_context_desc {void* mss_l4len_idx; void* seqnum_seed; void* type_tucmd_mlhl; void* vlan_macip_lens; } ;
typedef  TYPE_1__* if_pkt_info_t ;
struct TYPE_3__ {scalar_t__ ipi_vtag; scalar_t__ ipi_ehdrlen; int ipi_len; int ipi_csum_flags; int ipi_ip_hlen; int ipi_tcp_hlen; int ipi_tso_segsz; int ipi_flags; int ipi_ipproto; } ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_IP6_SCTP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_SCTP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_UDP ; 
 int CSUM_TSO ; 
 int ETHER_HDR_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int FALSE ; 
 int IPI_TX_IPV4 ; 
 int IPI_TX_IPV6 ; 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IXGBE_ADVTXD_DCMD_DEXT ; 
 int IXGBE_ADVTXD_DTYP_CTXT ; 
 int IXGBE_ADVTXD_L4LEN_SHIFT ; 
 int IXGBE_ADVTXD_MACLEN_SHIFT ; 
 int IXGBE_ADVTXD_MSS_SHIFT ; 
 int IXGBE_ADVTXD_PAYLEN_SHIFT ; 
 int IXGBE_ADVTXD_TUCMD_IPV4 ; 
 int IXGBE_ADVTXD_TUCMD_IPV6 ; 
 int IXGBE_ADVTXD_TUCMD_L4T_SCTP ; 
 int IXGBE_ADVTXD_TUCMD_L4T_TCP ; 
 int IXGBE_ADVTXD_TUCMD_L4T_UDP ; 
 int IXGBE_ADVTXD_VLAN_SHIFT ; 
 int IXGBE_TXD_POPTS_IXSM ; 
 int IXGBE_TXD_POPTS_TXSM ; 
 int TRUE ; 
 int htole16 (scalar_t__) ; 
 void* htole32 (int) ; 

__attribute__((used)) static int
ixgbe_tx_ctx_setup(struct ixgbe_adv_tx_context_desc *TXD, if_pkt_info_t pi)
{
	u32 vlan_macip_lens, type_tucmd_mlhl;
	u32 olinfo_status, mss_l4len_idx, pktlen, offload;
	u8  ehdrlen;

	offload = TRUE;
	olinfo_status = mss_l4len_idx = vlan_macip_lens = type_tucmd_mlhl = 0;
	/* VLAN MACLEN IPLEN */
	vlan_macip_lens |= (htole16(pi->ipi_vtag) << IXGBE_ADVTXD_VLAN_SHIFT);

	/*
	 * Some of our VF devices need a context descriptor for every
	 * packet.  That means the ehdrlen needs to be non-zero in order
	 * for the host driver not to flag a malicious event. The stack
	 * will most likely populate this for all other reasons of why
	 * this function was called.
	 */
	if (pi->ipi_ehdrlen == 0) {
		ehdrlen = ETHER_HDR_LEN;
		ehdrlen += (pi->ipi_vtag != 0) ? ETHER_VLAN_ENCAP_LEN : 0;
	} else
		ehdrlen = pi->ipi_ehdrlen;
	vlan_macip_lens |= ehdrlen << IXGBE_ADVTXD_MACLEN_SHIFT;

	pktlen = pi->ipi_len;
	/* First check if TSO is to be used */
	if (pi->ipi_csum_flags & CSUM_TSO) {
		/* This is used in the transmit desc in encap */
		pktlen = pi->ipi_len - ehdrlen - pi->ipi_ip_hlen - pi->ipi_tcp_hlen;
		mss_l4len_idx |= (pi->ipi_tso_segsz << IXGBE_ADVTXD_MSS_SHIFT);
		mss_l4len_idx |= (pi->ipi_tcp_hlen << IXGBE_ADVTXD_L4LEN_SHIFT);
	}

	olinfo_status |= pktlen << IXGBE_ADVTXD_PAYLEN_SHIFT;

	if (pi->ipi_flags & IPI_TX_IPV4) {
		type_tucmd_mlhl |= IXGBE_ADVTXD_TUCMD_IPV4;
		/* Tell transmit desc to also do IPv4 checksum. */
		if (pi->ipi_csum_flags & (CSUM_IP|CSUM_TSO))
			olinfo_status |= IXGBE_TXD_POPTS_IXSM << 8;
	} else if (pi->ipi_flags & IPI_TX_IPV6)
		type_tucmd_mlhl |= IXGBE_ADVTXD_TUCMD_IPV6;
	else
		offload = FALSE;

	vlan_macip_lens |= pi->ipi_ip_hlen;

	switch (pi->ipi_ipproto) {
	case IPPROTO_TCP:
		if (pi->ipi_csum_flags & (CSUM_IP_TCP | CSUM_IP6_TCP | CSUM_TSO))
			type_tucmd_mlhl |= IXGBE_ADVTXD_TUCMD_L4T_TCP;
		else
			offload = FALSE;
		break;
	case IPPROTO_UDP:
		if (pi->ipi_csum_flags & (CSUM_IP_UDP | CSUM_IP6_UDP))
			type_tucmd_mlhl |= IXGBE_ADVTXD_TUCMD_L4T_UDP;
		else
			offload = FALSE;
		break;
	case IPPROTO_SCTP:
		if (pi->ipi_csum_flags & (CSUM_IP_SCTP | CSUM_IP6_SCTP))
			type_tucmd_mlhl |= IXGBE_ADVTXD_TUCMD_L4T_SCTP;
		else
			offload = FALSE;
		break;
	default:
		offload = FALSE;
		break;
	}
/* Insert L4 checksum into data descriptors */
	if (offload)
		olinfo_status |= IXGBE_TXD_POPTS_TXSM << 8;

	type_tucmd_mlhl |= IXGBE_ADVTXD_DCMD_DEXT | IXGBE_ADVTXD_DTYP_CTXT;

	/* Now copy bits into descriptor */
	TXD->vlan_macip_lens = htole32(vlan_macip_lens);
	TXD->type_tucmd_mlhl = htole32(type_tucmd_mlhl);
	TXD->seqnum_seed = htole32(0);
	TXD->mss_l4len_idx = htole32(mss_l4len_idx);

	return (olinfo_status);
}