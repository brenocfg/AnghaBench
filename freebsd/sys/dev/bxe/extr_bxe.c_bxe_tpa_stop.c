#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_6__ {int csum_data; int csum_flags; int /*<<< orphan*/  flowid; int /*<<< orphan*/  ether_vtag; int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_len; } ;
struct eth_end_agg_rx_cqe {int /*<<< orphan*/  pkt_len; } ;
struct TYPE_5__ {struct mbuf* m; } ;
struct bxe_sw_tpa_info {int parsing_flags; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  len_on_bd; int /*<<< orphan*/  placement_offset; TYPE_1__ bd; } ;
struct bxe_softc {int /*<<< orphan*/  ifp; } ;
struct TYPE_7__ {int /*<<< orphan*/  mbuf_alloc_tpa; int /*<<< orphan*/  rx_tpa_pkts; int /*<<< orphan*/  rx_soft_errors; int /*<<< orphan*/  rx_ofld_frames_csum_tcp_udp; int /*<<< orphan*/  rx_ofld_frames_csum_ip; } ;
struct bxe_fastpath {int rx_tpa_queue_used; TYPE_4__* rx_tpa_info; TYPE_3__ eth_q_stats; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_SET_FLOWID (struct mbuf*) ; 
 int /*<<< orphan*/  BXE_TPA_STATE_STOP ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int /*<<< orphan*/  DBG_LRO ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int PARSING_FLAGS_INNER_VLAN_EXIST ; 
 int bxe_alloc_rx_tpa_mbuf (struct bxe_fastpath*,size_t) ; 
 int bxe_fill_frag_mbuf (struct bxe_softc*,struct bxe_fastpath*,struct bxe_sw_tpa_info*,size_t,size_t,struct mbuf*,struct eth_end_agg_rx_cqe*,size_t) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_input (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setrcvif (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
bxe_tpa_stop(struct bxe_softc          *sc,
             struct bxe_fastpath       *fp,
             struct bxe_sw_tpa_info    *tpa_info,
             uint16_t                  queue,
             uint16_t                  pages,
			 struct eth_end_agg_rx_cqe *cqe,
             uint16_t                  cqe_idx)
{
    if_t ifp = sc->ifp;
    struct mbuf *m;
    int rc = 0;

    BLOGD(sc, DBG_LRO,
          "fp[%02d].tpa[%02d] pad=%d pkt_len=%d pages=%d vlan=%d\n",
          fp->index, queue, tpa_info->placement_offset,
          le16toh(cqe->pkt_len), pages, tpa_info->vlan_tag);

    m = tpa_info->bd.m;

    /* allocate a replacement before modifying existing mbuf */
    rc = bxe_alloc_rx_tpa_mbuf(fp, queue);
    if (rc) {
        /* drop the frame and log an error */
        fp->eth_q_stats.rx_soft_errors++;
        goto bxe_tpa_stop_exit;
    }

    /* we have a replacement, fixup the current mbuf */
    m_adj(m, tpa_info->placement_offset);
    m->m_pkthdr.len = m->m_len = tpa_info->len_on_bd;

    /* mark the checksums valid (taken care of by the firmware) */
    fp->eth_q_stats.rx_ofld_frames_csum_ip++;
    fp->eth_q_stats.rx_ofld_frames_csum_tcp_udp++;
    m->m_pkthdr.csum_data = 0xffff;
    m->m_pkthdr.csum_flags |= (CSUM_IP_CHECKED |
                               CSUM_IP_VALID   |
                               CSUM_DATA_VALID |
                               CSUM_PSEUDO_HDR);

    /* aggregate all of the SGEs into a single mbuf */
    rc = bxe_fill_frag_mbuf(sc, fp, tpa_info, queue, pages, m, cqe, cqe_idx);
    if (rc) {
        /* drop the packet and log an error */
        fp->eth_q_stats.rx_soft_errors++;
        m_freem(m);
    } else {
        if (tpa_info->parsing_flags & PARSING_FLAGS_INNER_VLAN_EXIST) {
            m->m_pkthdr.ether_vtag = tpa_info->vlan_tag;
            m->m_flags |= M_VLANTAG;
        }

        /* assign packet to this interface interface */
        if_setrcvif(m, ifp);

#if __FreeBSD_version >= 800000
        /* specify what RSS queue was used for this flow */
        m->m_pkthdr.flowid = fp->index;
        BXE_SET_FLOWID(m);
#endif

        if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
        fp->eth_q_stats.rx_tpa_pkts++;

        /* pass the frame to the stack */
        if_input(ifp, m);
    }

    /* we passed an mbuf up the stack or dropped the frame */
    fp->eth_q_stats.mbuf_alloc_tpa--;

bxe_tpa_stop_exit:

    fp->rx_tpa_info[queue].state = BXE_TPA_STATE_STOP;
    fp->rx_tpa_queue_used &= ~(1 << queue);
}