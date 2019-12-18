#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ gso_segs; int /*<<< orphan*/  gso_size; } ;
union lio_tx_info {TYPE_2__ s; } ;
struct TYPE_16__ {int gatherptrs; int /*<<< orphan*/  datasize; } ;
struct TYPE_15__ {int iq_no; int ip_csum; int transport_csum; int gather; TYPE_11__ u; } ;
union lio_cmd_setup {TYPE_10__ s; scalar_t__ cmd_setup64; } ;
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct octeon_instr_irh {int priority; int vlan; } ;
struct octeon_device {TYPE_5__** instr_queue; } ;
struct TYPE_27__ {int csum_flags; int ether_vtag; int /*<<< orphan*/  tso_segsz; scalar_t__ len; } ;
struct mbuf {int m_flags; TYPE_9__ m_pkthdr; } ;
struct lio_mbuf_free_info {struct lio_gather* g; struct mbuf* mb; int /*<<< orphan*/  map; } ;
struct lio_request_list {struct lio_mbuf_free_info finfo; int /*<<< orphan*/  map; } ;
struct lio_iq_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_tot_bytes; scalar_t__ tx_done; int /*<<< orphan*/  tx_gso; int /*<<< orphan*/  tx_dmamap_fail; int /*<<< orphan*/  mbuf_defrag_failed; int /*<<< orphan*/  tx_iq_busy; } ;
struct TYPE_21__ {int q_no; } ;
struct TYPE_22__ {TYPE_3__ s; } ;
struct lio_instr_queue {int host_write_index; int /*<<< orphan*/  txtag; struct lio_request_list* request_list; TYPE_4__ txpciq; struct octeon_device* oct_dev; } ;
struct lio_gather {int sg_size; void* sg_dma_ptr; struct lio_data_pkt* sg; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ossp; int /*<<< orphan*/  irh; void* dptr; } ;
struct TYPE_18__ {TYPE_1__ cmd3; } ;
struct lio_data_pkt {int q_no; scalar_t__ datasize; TYPE_13__ cmd; int /*<<< orphan*/  reqtype; void** ptr; void* buf; } ;
struct TYPE_24__ {int /*<<< orphan*/  link_up; } ;
struct TYPE_25__ {TYPE_6__ s; } ;
struct TYPE_26__ {TYPE_7__ link; } ;
struct lio {int /*<<< orphan*/ * glist_lock; int /*<<< orphan*/ * ghead; TYPE_8__ linfo; int /*<<< orphan*/  ifstate; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_17__ {int /*<<< orphan*/  ds_len; void* ds_addr; } ;
typedef  TYPE_12__ bus_dma_segment_t ;
struct TYPE_23__ {struct lio_iq_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int CSUM_IP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_TSO ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_TCP ; 
 int CSUM_IP_TSO ; 
 int CSUM_IP_UDP ; 
 int EFBIG ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIO_CAST64 (int /*<<< orphan*/ ) ; 
 int LIO_IFSTATE_RUNNING ; 
 int LIO_IQ_SEND_FAILED ; 
 int LIO_MAX_SG ; 
 int /*<<< orphan*/  LIO_REQTYPE_NORESP_NET ; 
 int /*<<< orphan*/  LIO_REQTYPE_NORESP_NET_SG ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VLANTAG ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_12__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct lio_data_pkt*,int) ; 
 scalar_t__ howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_add_sg_size (struct lio_data_pkt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lio_delete_first_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int,...) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,...) ; 
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_iq_is_full (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_prepare_pci_cmd (struct octeon_device*,TYPE_13__*,union lio_cmd_setup*,int) ; 
 int lio_send_data_pkt (struct octeon_device*,struct lio_data_pkt*) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
lio_xmit(struct lio *lio, struct lio_instr_queue *iq,
	 struct mbuf **m_headp)
{
	struct lio_data_pkt		ndata;
	union lio_cmd_setup		cmdsetup;
	struct lio_mbuf_free_info	*finfo = NULL;
	struct octeon_device		*oct = iq->oct_dev;
	struct lio_iq_stats		*stats;
	struct octeon_instr_irh		*irh;
	struct lio_request_list		*tx_buf;
	union lio_tx_info		*tx_info;
	struct mbuf			*m_head;
	bus_dma_segment_t		segs[LIO_MAX_SG];
	bus_dmamap_t			map;
	uint64_t	dptr = 0;
	uint32_t	tag = 0;
	int		iq_no = 0;
	int		nsegs;
	int		status = 0;

	iq_no = iq->txpciq.s.q_no;
	tag = iq_no;
	stats = &oct->instr_queue[iq_no]->stats;
	tx_buf = iq->request_list + iq->host_write_index;

	/*
	 * Check for all conditions in which the current packet cannot be
	 * transmitted.
	 */
	if (!(atomic_load_acq_int(&lio->ifstate) & LIO_IFSTATE_RUNNING) ||
	    (!lio->linfo.link.s.link_up)) {
		lio_dev_info(oct, "Transmit failed link_status : %d\n",
			     lio->linfo.link.s.link_up);
		status = ENETDOWN;
		goto drop_packet;
	}

	if (lio_iq_is_full(oct, iq_no)) {
		/* Defer sending if queue is full */
		lio_dev_dbg(oct, "Transmit failed iq:%d full\n", iq_no);
		stats->tx_iq_busy++;
		return (ENOBUFS);
	}

	map = tx_buf->map;
	status = bus_dmamap_load_mbuf_sg(iq->txtag, map, *m_headp, segs, &nsegs,
					 BUS_DMA_NOWAIT);
	if (status == EFBIG) {
		struct mbuf	*m;

		m = m_defrag(*m_headp, M_NOWAIT);
		if (m == NULL) {
			stats->mbuf_defrag_failed++;
			goto drop_packet;
		}

		*m_headp = m;
		status = bus_dmamap_load_mbuf_sg(iq->txtag, map,
						 *m_headp, segs, &nsegs,
						 BUS_DMA_NOWAIT);
	}

	if (status == ENOMEM) {
		goto retry;
	} else if (status) {
		stats->tx_dmamap_fail++;
		lio_dev_dbg(oct, "bus_dmamap_load_mbuf_sg failed with error %d. iq:%d",
			    status, iq_no);
		goto drop_packet;
	}

	m_head = *m_headp;

	/* Info used to unmap and free the buffers. */
	finfo = &tx_buf->finfo;
	finfo->map = map;
	finfo->mb = m_head;

	/* Prepare the attributes for the data to be passed to OSI. */
	bzero(&ndata, sizeof(struct lio_data_pkt));

	ndata.buf = (void *)finfo;
	ndata.q_no = iq_no;
	ndata.datasize = m_head->m_pkthdr.len;

	cmdsetup.cmd_setup64 = 0;
	cmdsetup.s.iq_no = iq_no;

	if (m_head->m_pkthdr.csum_flags & CSUM_IP)
		cmdsetup.s.ip_csum = 1;

	if ((m_head->m_pkthdr.csum_flags & (CSUM_IP_TCP | CSUM_IP6_TCP)) ||
	    (m_head->m_pkthdr.csum_flags & (CSUM_IP_UDP | CSUM_IP6_UDP)))
		cmdsetup.s.transport_csum = 1;

	if (nsegs == 1) {
		cmdsetup.s.u.datasize = segs[0].ds_len;
		lio_prepare_pci_cmd(oct, &ndata.cmd, &cmdsetup, tag);

		dptr = segs[0].ds_addr;
		ndata.cmd.cmd3.dptr = dptr;
		ndata.reqtype = LIO_REQTYPE_NORESP_NET;

	} else {
		struct lio_gather	*g;
		int	i;

		mtx_lock(&lio->glist_lock[iq_no]);
		g = (struct lio_gather *)
			lio_delete_first_node(&lio->ghead[iq_no]);
		mtx_unlock(&lio->glist_lock[iq_no]);

		if (g == NULL) {
			lio_dev_err(oct,
				    "Transmit scatter gather: glist null!\n");
			goto retry;
		}

		cmdsetup.s.gather = 1;
		cmdsetup.s.u.gatherptrs = nsegs;
		lio_prepare_pci_cmd(oct, &ndata.cmd, &cmdsetup, tag);

		bzero(g->sg, g->sg_size);

		i = 0;
		while (nsegs--) {
			g->sg[(i >> 2)].ptr[(i & 3)] = segs[i].ds_addr;
			lio_add_sg_size(&g->sg[(i >> 2)], segs[i].ds_len,
					(i & 3));
			i++;
		}

		dptr = g->sg_dma_ptr;

		ndata.cmd.cmd3.dptr = dptr;
		finfo->g = g;

		ndata.reqtype = LIO_REQTYPE_NORESP_NET_SG;
	}

	irh = (struct octeon_instr_irh *)&ndata.cmd.cmd3.irh;
	tx_info = (union lio_tx_info *)&ndata.cmd.cmd3.ossp[0];

	if (m_head->m_pkthdr.csum_flags & (CSUM_IP_TSO | CSUM_IP6_TSO)) {
		tx_info->s.gso_size = m_head->m_pkthdr.tso_segsz;
		tx_info->s.gso_segs = howmany(m_head->m_pkthdr.len,
					      m_head->m_pkthdr.tso_segsz);
		stats->tx_gso++;
	}

	/* HW insert VLAN tag */
	if (m_head->m_flags & M_VLANTAG) {
		irh->priority = m_head->m_pkthdr.ether_vtag >> 13;
		irh->vlan = m_head->m_pkthdr.ether_vtag & 0xfff;
	}

	status = lio_send_data_pkt(oct, &ndata);
	if (status == LIO_IQ_SEND_FAILED)
		goto retry;

	if (tx_info->s.gso_segs)
		stats->tx_done += tx_info->s.gso_segs;
	else
		stats->tx_done++;

	stats->tx_tot_bytes += ndata.datasize;

	return (0);

retry:
	return (ENOBUFS);

drop_packet:
	stats->tx_dropped++;
	lio_dev_err(oct, "IQ%d Transmit dropped: %llu\n", iq_no,
		    LIO_CAST64(stats->tx_dropped));

	m_freem(*m_headp);
	*m_headp = NULL;

	return (status);
}