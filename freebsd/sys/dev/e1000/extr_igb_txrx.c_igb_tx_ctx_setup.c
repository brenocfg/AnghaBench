#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tx_ring {int me; int /*<<< orphan*/ * tx_base; struct adapter* adapter; } ;
struct e1000_adv_tx_context_desc {void* mss_l4len_idx; void* seqnum_seed; void* type_tucmd_mlhl; void* vlan_macip_lens; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; } ;
typedef  TYPE_3__* if_pkt_info_t ;
struct TYPE_8__ {int ipi_csum_flags; int ipi_len; size_t ipi_pidx; int ipi_mflags; int ipi_vtag; int ipi_ehdrlen; int ipi_etype; int ipi_ip_hlen; int ipi_ipproto; } ;

/* Variables and functions */
 int CSUM_IP6_SCTP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_SCTP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_UDP ; 
 int CSUM_TSO ; 
 int E1000_ADVTXD_DCMD_DEXT ; 
 int E1000_ADVTXD_DTYP_CTXT ; 
 int E1000_ADVTXD_MACLEN_SHIFT ; 
 int E1000_ADVTXD_PAYLEN_SHIFT ; 
 int E1000_ADVTXD_TUCMD_IPV4 ; 
 int E1000_ADVTXD_TUCMD_IPV6 ; 
 int E1000_ADVTXD_TUCMD_L4T_SCTP ; 
 int E1000_ADVTXD_TUCMD_L4T_TCP ; 
 int E1000_ADVTXD_TUCMD_L4T_UDP ; 
 int E1000_ADVTXD_VLAN_SHIFT ; 
 int E1000_TXD_POPTS_TXSM ; 
#define  ETHERTYPE_IP 132 
#define  ETHERTYPE_IPV6 131 
 int IGB_CSUM_OFFLOAD ; 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int M_VLANTAG ; 
 scalar_t__ e1000_82575 ; 
 void* htole32 (int) ; 
 int igb_tso_setup (struct tx_ring*,TYPE_3__*,int*,int*) ; 

__attribute__((used)) static int
igb_tx_ctx_setup(struct tx_ring *txr, if_pkt_info_t pi, u32 *cmd_type_len, u32 *olinfo_status)
{
	struct e1000_adv_tx_context_desc *TXD;
	struct adapter *adapter = txr->adapter; 
	u32 vlan_macip_lens, type_tucmd_mlhl;
	u32 mss_l4len_idx;
	mss_l4len_idx = vlan_macip_lens = type_tucmd_mlhl = 0;

	/* First check if TSO is to be used */
	if (pi->ipi_csum_flags & CSUM_TSO)
		return (igb_tso_setup(txr, pi, cmd_type_len, olinfo_status));

	/* Indicate the whole packet as payload when not doing TSO */
	*olinfo_status |= pi->ipi_len << E1000_ADVTXD_PAYLEN_SHIFT;

	/* Now ready a context descriptor */
	TXD = (struct e1000_adv_tx_context_desc *) &txr->tx_base[pi->ipi_pidx];

	/*
	** In advanced descriptors the vlan tag must 
	** be placed into the context descriptor. Hence
	** we need to make one even if not doing offloads.
	*/
	if (pi->ipi_mflags & M_VLANTAG) {
		vlan_macip_lens |= (pi->ipi_vtag << E1000_ADVTXD_VLAN_SHIFT);
	} else if ((pi->ipi_csum_flags & IGB_CSUM_OFFLOAD) == 0) {
		return (0);
	}
	
	/* Set the ether header length */
	vlan_macip_lens |= pi->ipi_ehdrlen << E1000_ADVTXD_MACLEN_SHIFT;

	switch(pi->ipi_etype) {
	case ETHERTYPE_IP:
		type_tucmd_mlhl |= E1000_ADVTXD_TUCMD_IPV4;
		break;
	case ETHERTYPE_IPV6:
		type_tucmd_mlhl |= E1000_ADVTXD_TUCMD_IPV6;
		break;
	default:
		break;
	}

	vlan_macip_lens |= pi->ipi_ip_hlen;
	type_tucmd_mlhl |= E1000_ADVTXD_DCMD_DEXT | E1000_ADVTXD_DTYP_CTXT;

	switch (pi->ipi_ipproto) {
	case IPPROTO_TCP:
		if (pi->ipi_csum_flags & (CSUM_IP_TCP | CSUM_IP6_TCP)) {
			type_tucmd_mlhl |= E1000_ADVTXD_TUCMD_L4T_TCP;
			*olinfo_status |= E1000_TXD_POPTS_TXSM << 8;
		}
		break;
	case IPPROTO_UDP:
		if (pi->ipi_csum_flags & (CSUM_IP_UDP | CSUM_IP6_UDP)) {
			type_tucmd_mlhl |= E1000_ADVTXD_TUCMD_L4T_UDP;
			*olinfo_status |= E1000_TXD_POPTS_TXSM << 8;
		}
		break;
	case IPPROTO_SCTP:
		if (pi->ipi_csum_flags & (CSUM_IP_SCTP | CSUM_IP6_SCTP)) {
			type_tucmd_mlhl |= E1000_ADVTXD_TUCMD_L4T_SCTP;
			*olinfo_status |= E1000_TXD_POPTS_TXSM << 8;
		}
		break;
	default:
		break;
	}

	/* 82575 needs the queue index added */
	if (adapter->hw.mac.type == e1000_82575)
		mss_l4len_idx = txr->me << 4;

	/* Now copy bits into descriptor */
	TXD->vlan_macip_lens = htole32(vlan_macip_lens);
	TXD->type_tucmd_mlhl = htole32(type_tucmd_mlhl);
	TXD->seqnum_seed = htole32(0);
	TXD->mss_l4len_idx = htole32(mss_l4len_idx);

	return (1);
}