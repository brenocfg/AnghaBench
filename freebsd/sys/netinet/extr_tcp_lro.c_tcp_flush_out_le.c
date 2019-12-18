#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct tcphdr {int th_sum; int /*<<< orphan*/  th_win; int /*<<< orphan*/  th_ack; } ;
struct tcpcb {int dummy; } ;
struct lro_entry {int append_cnt; int eh_type; scalar_t__ timestamp; int tsecr; int ulp_csum; TYPE_2__* m_head; int /*<<< orphan*/  tsval; int /*<<< orphan*/  window; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  p_len; struct ip* le_ip4; struct ip6_hdr* le_ip6; } ;
struct lro_ctrl {int lro_queued; TYPE_3__* ifp; } ;
struct ip6_hdr {int ip6_plen; } ;
struct ip {int ip_sum; int ip_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* if_input ) (TYPE_3__*,TYPE_2__*) ;} ;
struct TYPE_5__ {int csum_data; int lro_nsegs; int /*<<< orphan*/  len; void* csum_flags; } ;
struct TYPE_6__ {TYPE_1__ m_pkthdr; int /*<<< orphan*/ * m_nextpkt; } ;

/* Variables and functions */
 void* CSUM_DATA_VALID ; 
 void* CSUM_IP_CHECKED ; 
 void* CSUM_IP_VALID ; 
 void* CSUM_PSEUDO_HDR ; 
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int /*<<< orphan*/  ETHER_HDR_LEN ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ tcp_lro_csum_th (struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_lro_log (struct tcpcb*,struct lro_ctrl*,struct lro_entry*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_flush_out_le(struct tcpcb *tp, struct lro_ctrl *lc, struct lro_entry *le, int locked)
{
	if (le->append_cnt > 1) {
		struct tcphdr *th;
		uint16_t p_len;

		p_len = htons(le->p_len);
		switch (le->eh_type) {
#ifdef INET6
		case ETHERTYPE_IPV6:
		{
			struct ip6_hdr *ip6;

			ip6 = le->le_ip6;
			ip6->ip6_plen = p_len;
			th = (struct tcphdr *)(ip6 + 1);
			le->m_head->m_pkthdr.csum_flags = CSUM_DATA_VALID |
			    CSUM_PSEUDO_HDR;
			le->p_len += ETHER_HDR_LEN + sizeof(*ip6);
			break;
		}
#endif
#ifdef INET
		case ETHERTYPE_IP:
		{
			struct ip *ip4;
			uint32_t cl;
			uint16_t c;

			ip4 = le->le_ip4;
			/* Fix IP header checksum for new length. */
			c = ~ip4->ip_sum;
			cl = c;
			c = ~ip4->ip_len;
			cl += c + p_len;
			while (cl > 0xffff)
				cl = (cl >> 16) + (cl & 0xffff);
			c = cl;
			ip4->ip_sum = ~c;
			ip4->ip_len = p_len;
			th = (struct tcphdr *)(ip4 + 1);
			le->m_head->m_pkthdr.csum_flags = CSUM_DATA_VALID |
			    CSUM_PSEUDO_HDR | CSUM_IP_CHECKED | CSUM_IP_VALID;
			le->p_len += ETHER_HDR_LEN;
			break;
		}
#endif
		default:
			th = NULL;	/* Keep compiler happy. */
		}
		le->m_head->m_pkthdr.csum_data = 0xffff;
		le->m_head->m_pkthdr.len = le->p_len;

		/* Incorporate the latest ACK into the TCP header. */
		th->th_ack = le->ack_seq;
		th->th_win = le->window;
		/* Incorporate latest timestamp into the TCP header. */
		if (le->timestamp != 0) {
			uint32_t *ts_ptr;

			ts_ptr = (uint32_t *)(th + 1);
			ts_ptr[1] = htonl(le->tsval);
			ts_ptr[2] = le->tsecr;
		}
		/* Update the TCP header checksum. */
		le->ulp_csum += p_len;
		le->ulp_csum += tcp_lro_csum_th(th);
		while (le->ulp_csum > 0xffff)
			le->ulp_csum = (le->ulp_csum >> 16) +
			    (le->ulp_csum & 0xffff);
		th->th_sum = (le->ulp_csum & 0xffff);
		th->th_sum = ~th->th_sum;
		if (tp && locked) {
			tcp_lro_log(tp, lc, le, NULL, 7, 0, 0, 0, 0);
		}
	}
	/* 
	 * Break any chain, this is not set to NULL on the singleton 
	 * case m_nextpkt points to m_head. Other case set them 
	 * m_nextpkt to NULL in push_and_replace.
	 */
	le->m_head->m_nextpkt = NULL;
	le->m_head->m_pkthdr.lro_nsegs = le->append_cnt;
	if (tp && locked) {
		tcp_lro_log(tp, lc, le, le->m_head, 8, 0, 0, 0, 0);
	}
	(*lc->ifp->if_input)(lc->ifp, le->m_head);
	lc->lro_queued += le->append_cnt;
}