#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union al_udma_desc {int dummy; } al_udma_desc ;
struct device {int dummy; } ;
struct al_udma_q_params {int size; int cdesc_size; int /*<<< orphan*/ * cdesc_base; int /*<<< orphan*/ * desc_base; int /*<<< orphan*/  desc_phy_base; int /*<<< orphan*/  desc_phy_base_map; int /*<<< orphan*/  desc_phy_base_tag; } ;
struct al_eth_tx_buffer {int dummy; } ;
struct al_eth_ring {int sw_count; int descs_size; int hw_count; scalar_t__ next_to_clean; scalar_t__ next_to_use; TYPE_1__* tx_buffer_info; int /*<<< orphan*/  dma_buf_tag; void* cmpl_tq; int /*<<< orphan*/  cmpl_task; void* enqueue_tq; int /*<<< orphan*/  enqueue_task; int /*<<< orphan*/ * br; int /*<<< orphan*/  br_mtx; struct al_udma_q_params q_params; struct device* dev; } ;
struct al_eth_adapter {int /*<<< orphan*/  dev; scalar_t__ up; struct al_eth_ring* tx_ring; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dma_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BR_SIZE ; 
 int /*<<< orphan*/  AL_ETH_PKT_MAX_BUFS ; 
 int /*<<< orphan*/  AL_TSO_SIZE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_IFAL ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  PI_REALTIME ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct al_eth_ring*) ; 
 int al_dma_alloc_coherent (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  al_eth_start_xmit ; 
 int /*<<< orphan*/  al_eth_tx_cmpl_work ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (struct device*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_printf_dbg (struct device*,char*,int) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  taskqueue_start_threads (void**,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
al_eth_setup_tx_resources(struct al_eth_adapter *adapter, int qid)
{
	struct al_eth_ring *tx_ring = &adapter->tx_ring[qid];
	struct device *dev = tx_ring->dev;
	struct al_udma_q_params *q_params = &tx_ring->q_params;
	int size;
	int ret;

	if (adapter->up)
		return (0);

	size = sizeof(struct al_eth_tx_buffer) * tx_ring->sw_count;

	tx_ring->tx_buffer_info = malloc(size, M_IFAL, M_ZERO | M_WAITOK);
	if (tx_ring->tx_buffer_info == NULL)
		return (ENOMEM);

	tx_ring->descs_size = tx_ring->hw_count * sizeof(union al_udma_desc);
	q_params->size = tx_ring->hw_count;

	ret = al_dma_alloc_coherent(dev, &q_params->desc_phy_base_tag,
	    (bus_dmamap_t *)&q_params->desc_phy_base_map,
	    (bus_addr_t *)&q_params->desc_phy_base,
	    (void**)&q_params->desc_base, tx_ring->descs_size);
	if (ret != 0) {
		device_printf(dev, "failed to al_dma_alloc_coherent,"
		    " ret = %d\n", ret);
		return (ENOMEM);
	}

	if (q_params->desc_base == NULL)
		return (ENOMEM);

	device_printf_dbg(dev, "Initializing ring queues %d\n", qid);

	/* Allocate Ring Queue */
	mtx_init(&tx_ring->br_mtx, "AlRingMtx", NULL, MTX_DEF);
	tx_ring->br = buf_ring_alloc(AL_BR_SIZE, M_DEVBUF, M_WAITOK,
	    &tx_ring->br_mtx);
	if (tx_ring->br == NULL) {
		device_printf(dev, "Critical Failure setting up buf ring\n");
		return (ENOMEM);
	}

	/* Allocate taskqueues */
	TASK_INIT(&tx_ring->enqueue_task, 0, al_eth_start_xmit, tx_ring);
	tx_ring->enqueue_tq = taskqueue_create_fast("al_tx_enque", M_NOWAIT,
	    taskqueue_thread_enqueue, &tx_ring->enqueue_tq);
	taskqueue_start_threads(&tx_ring->enqueue_tq, 1, PI_NET, "%s txeq",
	    device_get_nameunit(adapter->dev));
	TASK_INIT(&tx_ring->cmpl_task, 0, al_eth_tx_cmpl_work, tx_ring);
	tx_ring->cmpl_tq = taskqueue_create_fast("al_tx_cmpl", M_NOWAIT,
	    taskqueue_thread_enqueue, &tx_ring->cmpl_tq);
	taskqueue_start_threads(&tx_ring->cmpl_tq, 1, PI_REALTIME, "%s txcq",
	    device_get_nameunit(adapter->dev));

	/* Setup DMA descriptor areas. */
	ret = bus_dma_tag_create(bus_get_dma_tag(dev),
	    1, 0,			/* alignment, bounds */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    AL_TSO_SIZE,		/* maxsize */
	    AL_ETH_PKT_MAX_BUFS,	/* nsegments */
	    PAGE_SIZE,			/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockfuncarg */
	    &tx_ring->dma_buf_tag);

	if (ret != 0) {
		device_printf(dev,"Unable to allocate dma_buf_tag, ret = %d\n",
		    ret);
		return (ret);
	}

	for (size = 0; size < tx_ring->sw_count; size++) {
		ret = bus_dmamap_create(tx_ring->dma_buf_tag, 0,
		    &tx_ring->tx_buffer_info[size].dma_map);
		if (ret != 0) {
			device_printf(dev, "Unable to map DMA TX "
			    "buffer memory [iter=%d]\n", size);
			return (ret);
		}
	}

	/* completion queue not used for tx */
	q_params->cdesc_base = NULL;
	/* size in bytes of the udma completion ring descriptor */
	q_params->cdesc_size = 8;
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	return (0);
}