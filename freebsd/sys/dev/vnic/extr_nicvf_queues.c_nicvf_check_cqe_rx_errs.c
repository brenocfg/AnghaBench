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
struct nicvf_hw_stats {int /*<<< orphan*/  rx_truncated_pkts; int /*<<< orphan*/  rx_l4_pclp; int /*<<< orphan*/  rx_tcp_offset_errs; int /*<<< orphan*/  rx_tcp_flag_errs; int /*<<< orphan*/  rx_l4_port_errs; int /*<<< orphan*/  rx_udp_len_errs; int /*<<< orphan*/  rx_l4_csum_errs; int /*<<< orphan*/  rx_l4_malformed; int /*<<< orphan*/  rx_l3_pclp; int /*<<< orphan*/  rx_ip_ttl_errs; int /*<<< orphan*/  rx_ip_payload_malformed; int /*<<< orphan*/  rx_ip_hdr_malformed; int /*<<< orphan*/  rx_ip_csum_errs; int /*<<< orphan*/  rx_ip_ver_errs; int /*<<< orphan*/  rx_l2_pclp; int /*<<< orphan*/  rx_l2_len_mismatch; int /*<<< orphan*/  rx_undersize; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_l2_hdr_malformed; int /*<<< orphan*/  rx_prel2_errs; int /*<<< orphan*/  rx_bgx_errs; int /*<<< orphan*/  rx_fcs_errs; int /*<<< orphan*/  rx_jabber_errs; int /*<<< orphan*/  rx_bgx_truncated_pkts; } ;
struct nicvf_drv_stats {int /*<<< orphan*/  rx_frames_ok; } ;
struct nicvf {struct nicvf_drv_stats drv_stats; struct nicvf_hw_stats hw_stats; } ;
struct cqe_rx_t {int err_opcode; int /*<<< orphan*/  err_level; } ;
struct cmp_queue {int dummy; } ;

/* Variables and functions */
#define  CQ_RX_ERROP_IP_CSUM_ERR 151 
#define  CQ_RX_ERROP_IP_HOP 150 
#define  CQ_RX_ERROP_IP_MAL 149 
#define  CQ_RX_ERROP_IP_MALD 148 
#define  CQ_RX_ERROP_IP_NOT 147 
#define  CQ_RX_ERROP_L2_LENMISM 146 
#define  CQ_RX_ERROP_L2_MAL 145 
#define  CQ_RX_ERROP_L2_OVERSIZE 144 
#define  CQ_RX_ERROP_L2_PCLP 143 
#define  CQ_RX_ERROP_L2_UNDERSIZE 142 
#define  CQ_RX_ERROP_L3_PCLP 141 
#define  CQ_RX_ERROP_L4_CHK 140 
#define  CQ_RX_ERROP_L4_MAL 139 
#define  CQ_RX_ERROP_L4_PCLP 138 
#define  CQ_RX_ERROP_L4_PORT 137 
#define  CQ_RX_ERROP_PREL2_ERR 136 
#define  CQ_RX_ERROP_RBDR_TRUNC 135 
#define  CQ_RX_ERROP_RE_FCS 134 
#define  CQ_RX_ERROP_RE_JABBER 133 
#define  CQ_RX_ERROP_RE_PARTIAL 132 
#define  CQ_RX_ERROP_RE_RX_CTL 131 
#define  CQ_RX_ERROP_TCP_FLAG 130 
#define  CQ_RX_ERROP_TCP_OFFSET 129 
#define  CQ_RX_ERROP_UDP_LEN 128 

int
nicvf_check_cqe_rx_errs(struct nicvf *nic, struct cmp_queue *cq,
    struct cqe_rx_t *cqe_rx)
{
	struct nicvf_hw_stats *stats = &nic->hw_stats;
	struct nicvf_drv_stats *drv_stats = &nic->drv_stats;

	if (!cqe_rx->err_level && !cqe_rx->err_opcode) {
		drv_stats->rx_frames_ok++;
		return (0);
	}

	switch (cqe_rx->err_opcode) {
	case CQ_RX_ERROP_RE_PARTIAL:
		stats->rx_bgx_truncated_pkts++;
		break;
	case CQ_RX_ERROP_RE_JABBER:
		stats->rx_jabber_errs++;
		break;
	case CQ_RX_ERROP_RE_FCS:
		stats->rx_fcs_errs++;
		break;
	case CQ_RX_ERROP_RE_RX_CTL:
		stats->rx_bgx_errs++;
		break;
	case CQ_RX_ERROP_PREL2_ERR:
		stats->rx_prel2_errs++;
		break;
	case CQ_RX_ERROP_L2_MAL:
		stats->rx_l2_hdr_malformed++;
		break;
	case CQ_RX_ERROP_L2_OVERSIZE:
		stats->rx_oversize++;
		break;
	case CQ_RX_ERROP_L2_UNDERSIZE:
		stats->rx_undersize++;
		break;
	case CQ_RX_ERROP_L2_LENMISM:
		stats->rx_l2_len_mismatch++;
		break;
	case CQ_RX_ERROP_L2_PCLP:
		stats->rx_l2_pclp++;
		break;
	case CQ_RX_ERROP_IP_NOT:
		stats->rx_ip_ver_errs++;
		break;
	case CQ_RX_ERROP_IP_CSUM_ERR:
		stats->rx_ip_csum_errs++;
		break;
	case CQ_RX_ERROP_IP_MAL:
		stats->rx_ip_hdr_malformed++;
		break;
	case CQ_RX_ERROP_IP_MALD:
		stats->rx_ip_payload_malformed++;
		break;
	case CQ_RX_ERROP_IP_HOP:
		stats->rx_ip_ttl_errs++;
		break;
	case CQ_RX_ERROP_L3_PCLP:
		stats->rx_l3_pclp++;
		break;
	case CQ_RX_ERROP_L4_MAL:
		stats->rx_l4_malformed++;
		break;
	case CQ_RX_ERROP_L4_CHK:
		stats->rx_l4_csum_errs++;
		break;
	case CQ_RX_ERROP_UDP_LEN:
		stats->rx_udp_len_errs++;
		break;
	case CQ_RX_ERROP_L4_PORT:
		stats->rx_l4_port_errs++;
		break;
	case CQ_RX_ERROP_TCP_FLAG:
		stats->rx_tcp_flag_errs++;
		break;
	case CQ_RX_ERROP_TCP_OFFSET:
		stats->rx_tcp_offset_errs++;
		break;
	case CQ_RX_ERROP_L4_PCLP:
		stats->rx_l4_pclp++;
		break;
	case CQ_RX_ERROP_RBDR_TRUNC:
		stats->rx_truncated_pkts++;
		break;
	}

	return (1);
}