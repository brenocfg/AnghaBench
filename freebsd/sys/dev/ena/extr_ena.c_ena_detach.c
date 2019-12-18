#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ena_stats_dev {int dummy; } ;
struct ena_hw_stats {int dummy; } ;
struct ena_com_dev {struct ena_com_dev* bus; } ;
struct ena_adapter {TYPE_1__* ifp; int /*<<< orphan*/  ioctl_sx; int /*<<< orphan*/  global_mtx; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev_stats; int /*<<< orphan*/  hw_stats; int /*<<< orphan*/  reset_tq; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  timer_service; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  counter_u64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * if_vlantrunk; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_RSS_ACTIVE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ena_adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ena_com_delete_host_info (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_rss_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_destroy_device (struct ena_adapter*,int) ; 
 int /*<<< orphan*/  ena_down (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_io_rings_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_counters (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ena_free_irqs (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_pci_resources (struct ena_adapter*) ; 
 int ena_free_rx_dma_tag (struct ena_adapter*) ; 
 int ena_free_tx_dma_tag (struct ena_adapter*) ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (TYPE_1__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_detach(device_t pdev)
{
	struct ena_adapter *adapter = device_get_softc(pdev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc;

	/* Make sure VLANS are not using driver */
	if (adapter->ifp->if_vlantrunk != NULL) {
		device_printf(adapter->pdev ,"VLAN is in use, detach first\n");
		return (EBUSY);
	}

	ether_ifdetach(adapter->ifp);

	/* Free reset task and callout */
	callout_drain(&adapter->timer_service);
	while (taskqueue_cancel(adapter->reset_tq, &adapter->reset_task, NULL))
		taskqueue_drain(adapter->reset_tq, &adapter->reset_task);
	taskqueue_free(adapter->reset_tq);

	sx_xlock(&adapter->ioctl_sx);
	ena_down(adapter);
	ena_destroy_device(adapter, true);
	sx_unlock(&adapter->ioctl_sx);

#ifdef DEV_NETMAP
	netmap_detach(adapter->ifp);
#endif /* DEV_NETMAP */

	ena_free_all_io_rings_resources(adapter);

	ena_free_counters((counter_u64_t *)&adapter->hw_stats,
	    sizeof(struct ena_hw_stats));
	ena_free_counters((counter_u64_t *)&adapter->dev_stats,
	    sizeof(struct ena_stats_dev));

	rc = ena_free_rx_dma_tag(adapter);
	if (unlikely(rc != 0))
		device_printf(adapter->pdev,
		    "Unmapped RX DMA tag associations\n");

	rc = ena_free_tx_dma_tag(adapter);
	if (unlikely(rc != 0))
		device_printf(adapter->pdev,
		    "Unmapped TX DMA tag associations\n");

	ena_free_irqs(adapter);

	ena_free_pci_resources(adapter);

	if (likely(ENA_FLAG_ISSET(ENA_FLAG_RSS_ACTIVE, adapter)))
		ena_com_rss_destroy(ena_dev);

	ena_com_delete_host_info(ena_dev);

	mtx_destroy(&adapter->global_mtx);
	sx_destroy(&adapter->ioctl_sx);

	if_free(adapter->ifp);

	if (ena_dev->bus != NULL)
		free(ena_dev->bus, M_DEVBUF);

	if (ena_dev != NULL)
		free(ena_dev, M_DEVBUF);

	return (bus_generic_detach(pdev));
}