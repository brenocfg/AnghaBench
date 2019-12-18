#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ena_stats_dev {int dummy; } ;
struct ena_llq_configurations {int dummy; } ;
struct ena_hw_stats {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;
struct ena_com_dev_get_features_ctx {TYPE_2__ dev_attr; TYPE_1__ offload; int /*<<< orphan*/  llq; } ;
struct ena_com_dev {scalar_t__ tx_mem_queue_type; struct ena_com_dev* bus; void* dmadev; } ;
struct ena_calc_queue_size_ctx {int /*<<< orphan*/  tx_queue_size; int /*<<< orphan*/  rx_queue_size; int /*<<< orphan*/  max_rx_sgl_size; int /*<<< orphan*/  max_tx_sgl_size; void* pdev; struct ena_com_dev_get_features_ctx* get_feat_ctx; struct ena_com_dev* ena_dev; int /*<<< orphan*/  member_0; } ;
struct ena_bus {scalar_t__ reg_bar_h; int /*<<< orphan*/  reg_bar_t; } ;
struct ena_adapter {int num_queues; struct ena_com_dev* ena_dev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  hw_stats; int /*<<< orphan*/  dev_stats; void* pdev; int /*<<< orphan*/  reset_tq; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  buf_ring_size; int /*<<< orphan*/  max_rx_sgl_size; int /*<<< orphan*/  max_tx_sgl_size; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  tx_offload_cap; int /*<<< orphan*/  keep_alive_timestamp; int /*<<< orphan*/  wd_active; int /*<<< orphan*/ * registers; int /*<<< orphan*/ * memory; int /*<<< orphan*/  missing_tx_threshold; int /*<<< orphan*/  missing_tx_max_queues; int /*<<< orphan*/  missing_tx_timeout; int /*<<< orphan*/  keep_alive_timeout; int /*<<< orphan*/  global_mtx; int /*<<< orphan*/  timer_service; int /*<<< orphan*/  ioctl_sx; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_KEEP_ALIVE_TO ; 
 int /*<<< orphan*/  DEFAULT_TX_CMP_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_TX_CMP_TO ; 
 int /*<<< orphan*/  DEFAULT_TX_MONITORED_QUEUES ; 
 int EFAULT ; 
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  ENA_ASSERT (int,char*,int) ; 
 int /*<<< orphan*/  ENA_DEFAULT_BUF_RING_SIZE ; 
 int /*<<< orphan*/  ENA_DEFAULT_RING_SIZE ; 
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_ZERO (struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_REGS_RESET_INIT_ERR ; 
 int /*<<< orphan*/  ENA_REGS_RESET_NORMAL ; 
 int /*<<< orphan*/  ENA_REG_BAR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (void*) ; 
 struct ena_adapter* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int /*<<< orphan*/  ena_alloc_counters (int /*<<< orphan*/ *,int) ; 
 int ena_calc_io_queue_num (struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int ena_calc_queue_size (struct ena_adapter*,struct ena_calc_queue_size_ctx*) ; 
 int /*<<< orphan*/  ena_com_admin_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_delete_host_info (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_dev_reset (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_destroy (struct ena_com_dev*) ; 
 int ena_device_init (struct ena_adapter*,void*,struct ena_com_dev_get_features_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_disable_msix (struct ena_adapter*) ; 
 int ena_enable_msix_and_set_admin_interrupts (struct ena_adapter*,int) ; 
 int /*<<< orphan*/  ena_free_all_io_rings_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_mgmnt_irq (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_pci_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_rx_dma_tag (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_tx_dma_tag (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_init_io_rings (struct ena_adapter*) ; 
 int ena_netmap_attach (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_reset_task ; 
 int ena_set_queues_placement_policy (void*,struct ena_com_dev*,int /*<<< orphan*/ *,struct ena_llq_configurations*) ; 
 int ena_setup_ifnet (void*,struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int ena_setup_rx_dma_tag (struct ena_adapter*) ; 
 int ena_setup_tx_dma_tag (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_sysctl_add_nodes (struct ena_adapter*) ; 
 int ena_version ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getsbinuptime () ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_default_llq_configurations (struct ena_llq_configurations*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_attach(device_t pdev)
{
	struct ena_com_dev_get_features_ctx get_feat_ctx;
	struct ena_llq_configurations llq_config;
	struct ena_calc_queue_size_ctx calc_queue_ctx = { 0 };
	static int version_printed;
	struct ena_adapter *adapter;
	struct ena_com_dev *ena_dev = NULL;
	const char *queue_type_str;
	int io_queue_num;
	int rid, rc;

	adapter = device_get_softc(pdev);
	adapter->pdev = pdev;

	mtx_init(&adapter->global_mtx, "ENA global mtx", NULL, MTX_DEF);
	sx_init(&adapter->ioctl_sx, "ENA ioctl sx");

	/* Set up the timer service */
	callout_init_mtx(&adapter->timer_service, &adapter->global_mtx, 0);
	adapter->keep_alive_timeout = DEFAULT_KEEP_ALIVE_TO;
	adapter->missing_tx_timeout = DEFAULT_TX_CMP_TO;
	adapter->missing_tx_max_queues = DEFAULT_TX_MONITORED_QUEUES;
	adapter->missing_tx_threshold = DEFAULT_TX_CMP_THRESHOLD;

	if (version_printed++ == 0)
		device_printf(pdev, "%s\n", ena_version);

	/* Allocate memory for ena_dev structure */
	ena_dev = malloc(sizeof(struct ena_com_dev), M_DEVBUF,
	    M_WAITOK | M_ZERO);

	adapter->ena_dev = ena_dev;
	ena_dev->dmadev = pdev;

	rid = PCIR_BAR(ENA_REG_BAR);
	adapter->memory = NULL;
	adapter->registers = bus_alloc_resource_any(pdev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (unlikely(adapter->registers == NULL)) {
		device_printf(pdev,
		    "unable to allocate bus resource: registers!\n");
		rc = ENOMEM;
		goto err_dev_free;
	}

	ena_dev->bus = malloc(sizeof(struct ena_bus), M_DEVBUF,
	    M_WAITOK | M_ZERO);

	/* Store register resources */
	((struct ena_bus*)(ena_dev->bus))->reg_bar_t =
	    rman_get_bustag(adapter->registers);
	((struct ena_bus*)(ena_dev->bus))->reg_bar_h =
	    rman_get_bushandle(adapter->registers);

	if (unlikely(((struct ena_bus*)(ena_dev->bus))->reg_bar_h == 0)) {
		device_printf(pdev, "failed to pmap registers bar\n");
		rc = ENXIO;
		goto err_bus_free;
	}

	ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;

	/* Initially clear all the flags */
	ENA_FLAG_ZERO(adapter);

	/* Device initialization */
	rc = ena_device_init(adapter, pdev, &get_feat_ctx, &adapter->wd_active);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "ENA device init failed! (err: %d)\n", rc);
		rc = ENXIO;
		goto err_bus_free;
	}

	set_default_llq_configurations(&llq_config);

	rc = ena_set_queues_placement_policy(pdev, ena_dev, &get_feat_ctx.llq,
	     &llq_config);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "failed to set placement policy\n");
		goto err_com_free;
	}

	if (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST)
		queue_type_str = "Regular";
	else
		queue_type_str = "Low Latency";
	device_printf(pdev, "Placement policy: %s\n", queue_type_str);

	adapter->keep_alive_timestamp = getsbinuptime();

	adapter->tx_offload_cap = get_feat_ctx.offload.tx;

	memcpy(adapter->mac_addr, get_feat_ctx.dev_attr.mac_addr,
	    ETHER_ADDR_LEN);

	calc_queue_ctx.ena_dev = ena_dev;
	calc_queue_ctx.get_feat_ctx = &get_feat_ctx;
	calc_queue_ctx.pdev = pdev;

	/* calculate IO queue number to create */
	io_queue_num = ena_calc_io_queue_num(adapter, &get_feat_ctx);

	ENA_ASSERT(io_queue_num > 0, "Invalid queue number: %d\n",
	    io_queue_num);
	adapter->num_queues = io_queue_num;

	adapter->max_mtu = get_feat_ctx.dev_attr.max_mtu;
	// Set the requested Rx ring size
	adapter->rx_ring_size = ENA_DEFAULT_RING_SIZE;
	/* calculatre ring sizes */
	rc = ena_calc_queue_size(adapter, &calc_queue_ctx);
	if (unlikely((rc != 0) || (io_queue_num <= 0))) {
		rc = EFAULT;
		goto err_com_free;
	}

	adapter->reset_reason = ENA_REGS_RESET_NORMAL;

	adapter->tx_ring_size = calc_queue_ctx.tx_queue_size;
	adapter->rx_ring_size = calc_queue_ctx.rx_queue_size;

	adapter->max_tx_sgl_size = calc_queue_ctx.max_tx_sgl_size;
	adapter->max_rx_sgl_size = calc_queue_ctx.max_rx_sgl_size;

	adapter->buf_ring_size = ENA_DEFAULT_BUF_RING_SIZE;

	/* set up dma tags for rx and tx buffers */
	rc = ena_setup_tx_dma_tag(adapter);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "Failed to create TX DMA tag\n");
		goto err_com_free;
	}

	rc = ena_setup_rx_dma_tag(adapter);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "Failed to create RX DMA tag\n");
		goto err_tx_tag_free;
	}

	/* initialize rings basic information */
	device_printf(pdev,
	    "Creating %d io queues. Rx queue size: %d, Tx queue size: %d\n",
	    io_queue_num,
	    calc_queue_ctx.rx_queue_size,
	    calc_queue_ctx.tx_queue_size);
	ena_init_io_rings(adapter);

	rc = ena_enable_msix_and_set_admin_interrupts(adapter, io_queue_num);
	if (unlikely(rc != 0)) {
		device_printf(pdev,
		    "Failed to enable and set the admin interrupts\n");
		goto err_io_free;
	}

	/* setup network interface */
	rc = ena_setup_ifnet(pdev, adapter, &get_feat_ctx);
	if (unlikely(rc != 0)) {
		device_printf(pdev, "Error with network interface setup\n");
		goto err_msix_free;
	}

	/* Initialize reset task queue */
	TASK_INIT(&adapter->reset_task, 0, ena_reset_task, adapter);
	adapter->reset_tq = taskqueue_create("ena_reset_enqueue",
	    M_WAITOK | M_ZERO, taskqueue_thread_enqueue, &adapter->reset_tq);
	taskqueue_start_threads(&adapter->reset_tq, 1, PI_NET,
	    "%s rstq", device_get_nameunit(adapter->pdev));

	/* Initialize statistics */
	ena_alloc_counters((counter_u64_t *)&adapter->dev_stats,
	    sizeof(struct ena_stats_dev));
	ena_alloc_counters((counter_u64_t *)&adapter->hw_stats,
	    sizeof(struct ena_hw_stats));
	ena_sysctl_add_nodes(adapter);

#ifdef DEV_NETMAP
	rc = ena_netmap_attach(adapter);
	if (rc != 0) {
		device_printf(pdev, "netmap attach failed: %d\n", rc);
		goto err_detach;
	}
#endif /* DEV_NETMAP */

	/* Tell the stack that the interface is not active */
	if_setdrvflagbits(adapter->ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);
	ENA_FLAG_SET_ATOMIC(ENA_FLAG_DEVICE_RUNNING, adapter);

	return (0);

#ifdef DEV_NETMAP
err_detach:
	ether_ifdetach(adapter->ifp);
#endif /* DEV_NETMAP */
err_msix_free:
	ena_com_dev_reset(adapter->ena_dev, ENA_REGS_RESET_INIT_ERR);
	ena_free_mgmnt_irq(adapter);
	ena_disable_msix(adapter);
err_io_free:
	ena_free_all_io_rings_resources(adapter);
	ena_free_rx_dma_tag(adapter);
err_tx_tag_free:
	ena_free_tx_dma_tag(adapter);
err_com_free:
	ena_com_admin_destroy(ena_dev);
	ena_com_delete_host_info(ena_dev);
	ena_com_mmio_reg_read_request_destroy(ena_dev);
err_bus_free:
	free(ena_dev->bus, M_DEVBUF);
	ena_free_pci_resources(adapter);
err_dev_free:
	free(ena_dev, M_DEVBUF);

	return (rc);
}