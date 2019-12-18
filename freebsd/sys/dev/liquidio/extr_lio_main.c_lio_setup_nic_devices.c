#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int num_iqueues; int num_oqueues; unsigned int base_queue; unsigned int gmx_port_id; } ;
union octeon_if_cfg {scalar_t__ if_cfg64; TYPE_2__ s; } ;
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct octeon_if_cfg_info {int dummy; } ;
struct lio_if_props {struct ifnet* ifp; int /*<<< orphan*/  gmxport; } ;
struct TYPE_18__ {int num_pf_rings; unsigned int pf_srn; } ;
struct octeon_device {int ifcount; unsigned int pf_num; struct lio_if_props props; TYPE_1__ sriov_info; } ;
struct lio_version {void* micro; void* minor; void* major; } ;
struct lio_soft_command {int wait_time; struct lio_soft_command* callback_arg; int /*<<< orphan*/  callback; scalar_t__ iq_no; scalar_t__ virtdptr; scalar_t__ ctxptr; scalar_t__ virtrptr; } ;
struct TYPE_23__ {int /*<<< orphan*/  link_status64; } ;
struct TYPE_24__ {TYPE_6__ link; int /*<<< orphan*/  gmxport; scalar_t__ hw_addr; TYPE_4__* txpciq; TYPE_3__* rxpciq; } ;
struct TYPE_25__ {TYPE_7__ linfo; scalar_t__ oqmask; scalar_t__ iqmask; } ;
struct lio_if_cfg_resp {int status; TYPE_8__ cfg_info; } ;
struct lio_if_cfg_context {scalar_t__ cond; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_22__ {int /*<<< orphan*/  link_status64; } ;
struct TYPE_17__ {int num_rxpciq; int num_txpciq; TYPE_12__* rxpciq; TYPE_10__* txpciq; scalar_t__ hw_addr; int /*<<< orphan*/  gmxport; TYPE_5__ link; } ;
struct lio {int ifidx; int /*<<< orphan*/  stats_interval; int /*<<< orphan*/  stats_timer; void* vlan_detach; void* vlan_attach; int /*<<< orphan*/  link_changes; int /*<<< orphan*/  rxq; int /*<<< orphan*/  rx_qsize; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_qsize; TYPE_13__ linfo; struct ifnet* ifp; struct octeon_device* oct_dev; } ;
struct ifnet {int /*<<< orphan*/  if_hw_tsomaxsegsize; int /*<<< orphan*/  if_hw_tsomaxsegcount; int /*<<< orphan*/  if_hw_tsomax; } ;
struct TYPE_26__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_21__ {int /*<<< orphan*/  txpciq64; } ;
struct TYPE_20__ {int /*<<< orphan*/  rxpciq64; } ;
struct TYPE_15__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_16__ {TYPE_11__ s; int /*<<< orphan*/  rxpciq64; } ;
struct TYPE_14__ {TYPE_9__ s; int /*<<< orphan*/  txpciq64; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ETHER_HDR_LEN ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lio*,int /*<<< orphan*/ ) ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWFILTER ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  LIO_BASE_MAJOR_VERSION ; 
 int /*<<< orphan*/  LIO_BASE_MICRO_VERSION ; 
 int /*<<< orphan*/  LIO_BASE_MINOR_VERSION ; 
 int /*<<< orphan*/  LIO_CAST64 (scalar_t__) ; 
 int LIO_CMD_FNV_ENABLE ; 
 int /*<<< orphan*/  LIO_CMD_LRO_ENABLE ; 
 int /*<<< orphan*/  LIO_CMD_RXCSUM_ENABLE ; 
 int /*<<< orphan*/  LIO_CMD_SET_FNV ; 
 int /*<<< orphan*/  LIO_CMD_TNL_RX_CSUM_CTL ; 
 int /*<<< orphan*/  LIO_CMD_TNL_TX_CSUM_CTL ; 
 int LIO_CMD_TXCSUM_ENABLE ; 
 int /*<<< orphan*/  LIO_CMD_VLAN_FILTER_CTL ; 
 int /*<<< orphan*/  LIO_DEFAULT_STATS_INTERVAL ; 
 int /*<<< orphan*/  LIO_IFSTATE_DROQ_OPS ; 
 int /*<<< orphan*/  LIO_IFSTATE_REGISTERED ; 
 int LIO_IQ_SEND_FAILED ; 
 int LIO_LROIPV4 ; 
 int LIO_LROIPV6 ; 
 int /*<<< orphan*/  LIO_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  LIO_MAX_SG ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC_IF_CFG ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC_INFO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int bitcount64 (scalar_t__) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 void* htobe16 (int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int if_getcapenable (struct ifnet*) ; 
 int /*<<< orphan*/  if_setsoftc (struct ifnet*,struct lio*) ; 
 int /*<<< orphan*/  lio_add_hw_stats (struct lio*) ; 
 struct lio_soft_command* lio_alloc_soft_command (struct octeon_device*,int,int,int) ; 
 int /*<<< orphan*/  lio_destroy_nic_device (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int,...) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,...) ; 
 int /*<<< orphan*/  lio_free_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_get_device_id (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_get_rx_qsize (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_get_tx_qsize (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_hwlro ; 
 int /*<<< orphan*/  lio_if_cfg_callback ; 
 int /*<<< orphan*/  lio_ifstate_set (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_init_ifnet (struct lio*) ; 
 int /*<<< orphan*/  lio_link_info ; 
 int /*<<< orphan*/  lio_prepare_soft_command (struct octeon_device*,struct lio_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_register_dispatch_fn (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct octeon_device*) ; 
 scalar_t__ lio_rss ; 
 scalar_t__ lio_send_rss_param (struct lio*) ; 
 int lio_send_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_set_feature (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lio_set_rxcsum_command (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_setup_glists (struct octeon_device*,struct lio*,int) ; 
 scalar_t__ lio_setup_io_queues (struct octeon_device*,int,int,int) ; 
 scalar_t__ lio_setup_rx_oom_poll_fn (struct ifnet*) ; 
 int /*<<< orphan*/  lio_sleep_cond (struct octeon_device*,scalar_t__*) ; 
 int /*<<< orphan*/  lio_swap_8B_data (scalar_t__*,int) ; 
 scalar_t__ lio_tcp_lro_init (struct octeon_device*,struct ifnet*) ; 
 int /*<<< orphan*/  lio_vlan_rx_add_vid ; 
 int /*<<< orphan*/  lio_vlan_rx_kill_vid ; 
 struct lio* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static int
lio_setup_nic_devices(struct octeon_device *octeon_dev)
{
	union		octeon_if_cfg if_cfg;
	struct lio	*lio = NULL;
	struct ifnet	*ifp = NULL;
	struct lio_version		*vdata;
	struct lio_soft_command		*sc;
	struct lio_if_cfg_context	*ctx;
	struct lio_if_cfg_resp		*resp;
	struct lio_if_props		*props;
	int		num_iqueues, num_oqueues, retval;
	unsigned int	base_queue;
	unsigned int	gmx_port_id;
	uint32_t	ctx_size, data_size;
	uint32_t	ifidx_or_pfnum, resp_size;
	uint8_t		mac[ETHER_HDR_LEN], i, j;

	/* This is to handle link status changes */
	lio_register_dispatch_fn(octeon_dev, LIO_OPCODE_NIC,
				 LIO_OPCODE_NIC_INFO,
				 lio_link_info, octeon_dev);

	for (i = 0; i < octeon_dev->ifcount; i++) {
		resp_size = sizeof(struct lio_if_cfg_resp);
		ctx_size = sizeof(struct lio_if_cfg_context);
		data_size = sizeof(struct lio_version);
		sc = lio_alloc_soft_command(octeon_dev, data_size, resp_size,
					    ctx_size);
		if (sc == NULL)
			return (ENOMEM);

		resp = (struct lio_if_cfg_resp *)sc->virtrptr;
		ctx = (struct lio_if_cfg_context *)sc->ctxptr;
		vdata = (struct lio_version *)sc->virtdptr;

		*((uint64_t *)vdata) = 0;
		vdata->major = htobe16(LIO_BASE_MAJOR_VERSION);
		vdata->minor = htobe16(LIO_BASE_MINOR_VERSION);
		vdata->micro = htobe16(LIO_BASE_MICRO_VERSION);

		num_iqueues = octeon_dev->sriov_info.num_pf_rings;
		num_oqueues = octeon_dev->sriov_info.num_pf_rings;
		base_queue = octeon_dev->sriov_info.pf_srn;

		gmx_port_id = octeon_dev->pf_num;
		ifidx_or_pfnum = octeon_dev->pf_num;

		lio_dev_dbg(octeon_dev, "requesting config for interface %d, iqs %d, oqs %d\n",
			    ifidx_or_pfnum, num_iqueues, num_oqueues);
		ctx->cond = 0;
		ctx->octeon_id = lio_get_device_id(octeon_dev);

		if_cfg.if_cfg64 = 0;
		if_cfg.s.num_iqueues = num_iqueues;
		if_cfg.s.num_oqueues = num_oqueues;
		if_cfg.s.base_queue = base_queue;
		if_cfg.s.gmx_port_id = gmx_port_id;

		sc->iq_no = 0;

		lio_prepare_soft_command(octeon_dev, sc, LIO_OPCODE_NIC,
					 LIO_OPCODE_NIC_IF_CFG, 0,
					 if_cfg.if_cfg64, 0);

		sc->callback = lio_if_cfg_callback;
		sc->callback_arg = sc;
		sc->wait_time = 3000;

		retval = lio_send_soft_command(octeon_dev, sc);
		if (retval == LIO_IQ_SEND_FAILED) {
			lio_dev_err(octeon_dev, "iq/oq config failed status: %x\n",
				    retval);
			/* Soft instr is freed by driver in case of failure. */
			goto setup_nic_dev_fail;
		}

		/*
		 * Sleep on a wait queue till the cond flag indicates that the
		 * response arrived or timed-out.
		 */
		lio_sleep_cond(octeon_dev, &ctx->cond);

		retval = resp->status;
		if (retval) {
			lio_dev_err(octeon_dev, "iq/oq config failed\n");
			goto setup_nic_dev_fail;
		}

		lio_swap_8B_data((uint64_t *)(&resp->cfg_info),
				 (sizeof(struct octeon_if_cfg_info)) >> 3);

		num_iqueues = bitcount64(resp->cfg_info.iqmask);
		num_oqueues = bitcount64(resp->cfg_info.oqmask);

		if (!(num_iqueues) || !(num_oqueues)) {
			lio_dev_err(octeon_dev,
				    "Got bad iqueues (%016llX) or oqueues (%016llX) from firmware.\n",
				    LIO_CAST64(resp->cfg_info.iqmask),
				    LIO_CAST64(resp->cfg_info.oqmask));
			goto setup_nic_dev_fail;
		}

		lio_dev_dbg(octeon_dev,
			    "interface %d, iqmask %016llx, oqmask %016llx, numiqueues %d, numoqueues %d\n",
			    i, LIO_CAST64(resp->cfg_info.iqmask),
			    LIO_CAST64(resp->cfg_info.oqmask),
			    num_iqueues, num_oqueues);

		ifp = if_alloc(IFT_ETHER);

		if (ifp == NULL) {
			lio_dev_err(octeon_dev, "Device allocation failed\n");
			goto setup_nic_dev_fail;
		}

		lio = malloc(sizeof(struct lio), M_DEVBUF, M_NOWAIT | M_ZERO);

		if (lio == NULL) {
			lio_dev_err(octeon_dev, "Lio allocation failed\n");
			goto setup_nic_dev_fail;
		}

		if_setsoftc(ifp, lio);

		ifp->if_hw_tsomax = LIO_MAX_FRAME_SIZE;
		ifp->if_hw_tsomaxsegcount = LIO_MAX_SG;
		ifp->if_hw_tsomaxsegsize = PAGE_SIZE;

		lio->ifidx = ifidx_or_pfnum;

		props = &octeon_dev->props;
		props->gmxport = resp->cfg_info.linfo.gmxport;
		props->ifp = ifp;

		lio->linfo.num_rxpciq = num_oqueues;
		lio->linfo.num_txpciq = num_iqueues;
		for (j = 0; j < num_oqueues; j++) {
			lio->linfo.rxpciq[j].rxpciq64 =
			    resp->cfg_info.linfo.rxpciq[j].rxpciq64;
		}

		for (j = 0; j < num_iqueues; j++) {
			lio->linfo.txpciq[j].txpciq64 =
			    resp->cfg_info.linfo.txpciq[j].txpciq64;
		}

		lio->linfo.hw_addr = resp->cfg_info.linfo.hw_addr;
		lio->linfo.gmxport = resp->cfg_info.linfo.gmxport;
		lio->linfo.link.link_status64 =
		    resp->cfg_info.linfo.link.link_status64;

		/*
		 * Point to the properties for octeon device to which this
		 * interface belongs.
		 */
		lio->oct_dev = octeon_dev;
		lio->ifp = ifp;

		lio_dev_dbg(octeon_dev, "if%d gmx: %d hw_addr: 0x%llx\n", i,
			    lio->linfo.gmxport, LIO_CAST64(lio->linfo.hw_addr));
		lio_init_ifnet(lio);
		/* 64-bit swap required on LE machines */
		lio_swap_8B_data(&lio->linfo.hw_addr, 1);
		for (j = 0; j < 6; j++)
			mac[j] = *((uint8_t *)(
				   ((uint8_t *)&lio->linfo.hw_addr) + 2 + j));

		ether_ifattach(ifp, mac);

		/*
		 * By default all interfaces on a single Octeon uses the same
		 * tx and rx queues
		 */
		lio->txq = lio->linfo.txpciq[0].s.q_no;
		lio->rxq = lio->linfo.rxpciq[0].s.q_no;
		if (lio_setup_io_queues(octeon_dev, i, lio->linfo.num_txpciq,
					lio->linfo.num_rxpciq)) {
			lio_dev_err(octeon_dev, "I/O queues creation failed\n");
			goto setup_nic_dev_fail;
		}

		lio_ifstate_set(lio, LIO_IFSTATE_DROQ_OPS);

		lio->tx_qsize = lio_get_tx_qsize(octeon_dev, lio->txq);
		lio->rx_qsize = lio_get_rx_qsize(octeon_dev, lio->rxq);

		if (lio_setup_glists(octeon_dev, lio, num_iqueues)) {
			lio_dev_err(octeon_dev, "Gather list allocation failed\n");
			goto setup_nic_dev_fail;
		}

		if ((lio_hwlro == 0) && lio_tcp_lro_init(octeon_dev, ifp))
			goto setup_nic_dev_fail;

		if (lio_hwlro &&
		    (if_getcapenable(ifp) & IFCAP_LRO) &&
		    (if_getcapenable(ifp) & IFCAP_RXCSUM) &&
		    (if_getcapenable(ifp) & IFCAP_RXCSUM_IPV6))
			lio_set_feature(ifp, LIO_CMD_LRO_ENABLE,
					LIO_LROIPV4 | LIO_LROIPV6);

		if ((if_getcapenable(ifp) & IFCAP_VLAN_HWFILTER))
			lio_set_feature(ifp, LIO_CMD_VLAN_FILTER_CTL, 1);
		else
			lio_set_feature(ifp, LIO_CMD_VLAN_FILTER_CTL, 0);

		if (lio_setup_rx_oom_poll_fn(ifp))
			goto setup_nic_dev_fail;

		lio_dev_dbg(octeon_dev, "Setup NIC ifidx:%d mac:%02x%02x%02x%02x%02x%02x\n",
			    i, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		lio->link_changes++;

		lio_ifstate_set(lio, LIO_IFSTATE_REGISTERED);

		/*
		 * Sending command to firmware to enable Rx checksum offload
		 * by default at the time of setup of Liquidio driver for
		 * this device
		 */
		lio_set_rxcsum_command(ifp, LIO_CMD_TNL_RX_CSUM_CTL,
				       LIO_CMD_RXCSUM_ENABLE);
		lio_set_feature(ifp, LIO_CMD_TNL_TX_CSUM_CTL,
				LIO_CMD_TXCSUM_ENABLE);

#ifdef RSS
		if (lio_rss) {
			if (lio_send_rss_param(lio))
				goto setup_nic_dev_fail;
		} else
#endif	/* RSS */

			lio_set_feature(ifp, LIO_CMD_SET_FNV,
					LIO_CMD_FNV_ENABLE);

		lio_dev_dbg(octeon_dev, "NIC ifidx:%d Setup successful\n", i);

		lio_free_soft_command(octeon_dev, sc);
		lio->vlan_attach =
		    EVENTHANDLER_REGISTER(vlan_config,
					  lio_vlan_rx_add_vid, lio,
					  EVENTHANDLER_PRI_FIRST);
		lio->vlan_detach =
		    EVENTHANDLER_REGISTER(vlan_unconfig,
					  lio_vlan_rx_kill_vid, lio,
					  EVENTHANDLER_PRI_FIRST);

		/* Update stats periodically */
		callout_init(&lio->stats_timer, 0);
		lio->stats_interval = LIO_DEFAULT_STATS_INTERVAL;

		lio_add_hw_stats(lio);
	}

	return (0);

setup_nic_dev_fail:

	lio_free_soft_command(octeon_dev, sc);

	while (i--) {
		lio_dev_err(octeon_dev, "NIC ifidx:%d Setup failed\n", i);
		lio_destroy_nic_device(octeon_dev, i);
	}

	return (ENODEV);
}