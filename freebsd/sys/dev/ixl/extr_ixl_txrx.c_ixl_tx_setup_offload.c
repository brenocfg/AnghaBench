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
typedef  int u32 ;
struct udphdr {int dummy; } ;
struct sctphdr {int dummy; } ;
struct ixl_tx_queue {int dummy; } ;
typedef  TYPE_1__* if_pkt_info_t ;
struct TYPE_3__ {int ipi_etype; int ipi_csum_flags; int ipi_ehdrlen; int ipi_ip_hlen; int ipi_ipproto; int ipi_tcp_hlen; } ;

/* Variables and functions */
#define  ETHERTYPE_IP 132 
#define  ETHERTYPE_IPV6 131 
 int I40E_TX_DESC_CMD_IIPT_IPV4 ; 
 int I40E_TX_DESC_CMD_IIPT_IPV4_CSUM ; 
 int I40E_TX_DESC_CMD_IIPT_IPV6 ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_SCTP ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_TCP ; 
 int I40E_TX_DESC_CMD_L4T_EOFT_UDP ; 
 int I40E_TX_DESC_LENGTH_IPLEN_SHIFT ; 
 int I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT ; 
 int I40E_TX_DESC_LENGTH_MACLEN_SHIFT ; 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IXL_CSUM_IPV4 ; 
 int IXL_CSUM_SCTP ; 
 int IXL_CSUM_TCP ; 
 int IXL_CSUM_UDP ; 
 int /*<<< orphan*/  MPASS (int) ; 

__attribute__((used)) static void
ixl_tx_setup_offload(struct ixl_tx_queue *que,
    if_pkt_info_t pi, u32 *cmd, u32 *off)
{
	switch (pi->ipi_etype) {
#ifdef INET
		case ETHERTYPE_IP:
			if (pi->ipi_csum_flags & IXL_CSUM_IPV4)
				*cmd |= I40E_TX_DESC_CMD_IIPT_IPV4_CSUM;
			else
				*cmd |= I40E_TX_DESC_CMD_IIPT_IPV4;
			break;
#endif
#ifdef INET6
		case ETHERTYPE_IPV6:
			*cmd |= I40E_TX_DESC_CMD_IIPT_IPV6;
			break;
#endif
		default:
			break;
	}

	*off |= (pi->ipi_ehdrlen >> 1) << I40E_TX_DESC_LENGTH_MACLEN_SHIFT;
	*off |= (pi->ipi_ip_hlen >> 2) << I40E_TX_DESC_LENGTH_IPLEN_SHIFT;

	switch (pi->ipi_ipproto) {
		case IPPROTO_TCP:
			if (pi->ipi_csum_flags & IXL_CSUM_TCP) {
				*cmd |= I40E_TX_DESC_CMD_L4T_EOFT_TCP;
				*off |= (pi->ipi_tcp_hlen >> 2) <<
				    I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
				/* Check for NO_HEAD MDD event */
				MPASS(pi->ipi_tcp_hlen != 0);
			}
			break;
		case IPPROTO_UDP:
			if (pi->ipi_csum_flags & IXL_CSUM_UDP) {
				*cmd |= I40E_TX_DESC_CMD_L4T_EOFT_UDP;
				*off |= (sizeof(struct udphdr) >> 2) <<
				    I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
			}
			break;
		case IPPROTO_SCTP:
			if (pi->ipi_csum_flags & IXL_CSUM_SCTP) {
				*cmd |= I40E_TX_DESC_CMD_L4T_EOFT_SCTP;
				*off |= (sizeof(struct sctphdr) >> 2) <<
				    I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
			}
			/* Fall Thru */
		default:
			break;
	}
}