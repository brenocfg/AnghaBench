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
struct ena_adapter {TYPE_1__* msix_entries; TYPE_2__* irq_tbl; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; struct ena_adapter* data; int /*<<< orphan*/ * handler; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_IRQNAME_SIZE ; 
 size_t ENA_MGMNT_IRQ_IDX ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
ena_setup_mgmnt_intr(struct ena_adapter *adapter)
{

	snprintf(adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].name,
	    ENA_IRQNAME_SIZE, "ena-mgmnt@pci:%s",
	    device_get_nameunit(adapter->pdev));
	/*
	 * Handler is NULL on purpose, it will be set
	 * when mgmnt interrupt is acquired
	 */
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].handler = NULL;
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].data = adapter;
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].vector =
	    adapter->msix_entries[ENA_MGMNT_IRQ_IDX].vector;
}