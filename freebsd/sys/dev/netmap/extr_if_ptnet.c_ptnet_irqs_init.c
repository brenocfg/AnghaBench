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
struct ptnet_softc {int num_rings; int num_tx_rings; int /*<<< orphan*/  dev; struct ptnet_queue* queues; int /*<<< orphan*/ * msix_mem; } ;
struct ptnet_queue {int /*<<< orphan*/  taskq; int /*<<< orphan*/  task; int /*<<< orphan*/ * irq; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPU_FIRST () ; 
 int CPU_NEXT (int) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIY_MSIX ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  PTNETMAP_MSIX_PCI_BAR ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*,int),struct ptnet_queue*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_bind_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void (*) (void*),struct ptnet_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptnet_irqs_fini (struct ptnet_softc*) ; 
 void ptnet_rx_intr (void*) ; 
 void ptnet_rx_task (void*,int) ; 
 void ptnet_tx_intr (void*) ; 
 void ptnet_tx_task (void*,int) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
ptnet_irqs_init(struct ptnet_softc *sc)
{
	int rid = PCIR_BAR(PTNETMAP_MSIX_PCI_BAR);
	int nvecs = sc->num_rings;
	device_t dev = sc->dev;
	int err = ENOSPC;
	int cpu_cur;
	int i;

	if (pci_find_cap(dev, PCIY_MSIX, NULL) != 0)  {
		device_printf(dev, "Could not find MSI-X capability\n");
		return (ENXIO);
	}

	sc->msix_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
					      &rid, RF_ACTIVE);
	if (sc->msix_mem == NULL) {
		device_printf(dev, "Failed to allocate MSIX PCI BAR\n");
		return (ENXIO);
	}

	if (pci_msix_count(dev) < nvecs) {
		device_printf(dev, "Not enough MSI-X vectors\n");
		goto err_path;
	}

	err = pci_alloc_msix(dev, &nvecs);
	if (err) {
		device_printf(dev, "Failed to allocate MSI-X vectors\n");
		goto err_path;
	}

	for (i = 0; i < nvecs; i++) {
		struct ptnet_queue *pq = sc->queues + i;

		rid = i + 1;
		pq->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
						 RF_ACTIVE);
		if (pq->irq == NULL) {
			device_printf(dev, "Failed to allocate interrupt "
					   "for queue #%d\n", i);
			err = ENOSPC;
			goto err_path;
		}
	}

	cpu_cur = CPU_FIRST();
	for (i = 0; i < nvecs; i++) {
		struct ptnet_queue *pq = sc->queues + i;
		void (*handler)(void *) = ptnet_tx_intr;

		if (i >= sc->num_tx_rings) {
			handler = ptnet_rx_intr;
		}
		err = bus_setup_intr(dev, pq->irq, INTR_TYPE_NET | INTR_MPSAFE,
				     NULL /* intr_filter */, handler,
				     pq, &pq->cookie);
		if (err) {
			device_printf(dev, "Failed to register intr handler "
					   "for queue #%d\n", i);
			goto err_path;
		}

		bus_describe_intr(dev, pq->irq, pq->cookie, "q%d", i);
#if 0
		bus_bind_intr(sc->dev, pq->irq, cpu_cur);
#endif
		cpu_cur = CPU_NEXT(cpu_cur);
	}

	device_printf(dev, "Allocated %d MSI-X vectors\n", nvecs);

	cpu_cur = CPU_FIRST();
	for (i = 0; i < nvecs; i++) {
		struct ptnet_queue *pq = sc->queues + i;
		static void (*handler)(void *context, int pending);

		handler = (i < sc->num_tx_rings) ? ptnet_tx_task : ptnet_rx_task;

		TASK_INIT(&pq->task, 0, handler, pq);
		pq->taskq = taskqueue_create_fast("ptnet_queue", M_NOWAIT,
					taskqueue_thread_enqueue, &pq->taskq);
		taskqueue_start_threads(&pq->taskq, 1, PI_NET, "%s-pq-%d",
					device_get_nameunit(sc->dev), cpu_cur);
		cpu_cur = CPU_NEXT(cpu_cur);
	}

	return 0;
err_path:
	ptnet_irqs_fini(sc);
	return err;
}