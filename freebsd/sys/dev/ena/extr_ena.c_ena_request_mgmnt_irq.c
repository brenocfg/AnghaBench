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
struct ena_irq {int requested; int /*<<< orphan*/ * res; int /*<<< orphan*/  vector; int /*<<< orphan*/  cookie; int /*<<< orphan*/  data; } ;
struct ena_adapter {int /*<<< orphan*/  pdev; struct ena_irq* irq_tbl; } ;

/* Variables and functions */
 int ENA_ADMQ ; 
 int ENA_INFO ; 
 size_t ENA_MGMNT_IRQ_IDX ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 unsigned long RF_ACTIVE ; 
 unsigned long RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ena_intr_msix_mgmnt ; 
 int /*<<< orphan*/  ena_trace (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_request_mgmnt_irq(struct ena_adapter *adapter)
{
	struct ena_irq *irq;
	unsigned long flags;
	int rc, rcc;

	flags = RF_ACTIVE | RF_SHAREABLE;

	irq = &adapter->irq_tbl[ENA_MGMNT_IRQ_IDX];
	irq->res = bus_alloc_resource_any(adapter->pdev, SYS_RES_IRQ,
	    &irq->vector, flags);

	if (unlikely(irq->res == NULL)) {
		device_printf(adapter->pdev, "could not allocate "
		    "irq vector: %d\n", irq->vector);
		return (ENXIO);
	}

	rc = bus_setup_intr(adapter->pdev, irq->res,
	    INTR_TYPE_NET | INTR_MPSAFE, NULL, ena_intr_msix_mgmnt,
	    irq->data, &irq->cookie);
	if (unlikely(rc != 0)) {
		device_printf(adapter->pdev, "failed to register "
		    "interrupt handler for irq %ju: %d\n",
		    rman_get_start(irq->res), rc);
		goto err_res_free;
	}
	irq->requested = true;

	return (rc);

err_res_free:
	ena_trace(ENA_INFO | ENA_ADMQ, "releasing resource for irq %d\n",
	    irq->vector);
	rcc = bus_release_resource(adapter->pdev, SYS_RES_IRQ,
	    irq->vector, irq->res);
	if (unlikely(rcc != 0))
		device_printf(adapter->pdev, "dev has no parent while "
		    "releasing res for irq: %d\n", irq->vector);
	irq->res = NULL;

	return (rc);
}