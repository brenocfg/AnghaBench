#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct ecore_eth_stats {int dummy; } ;
struct ecore_dev {int /*<<< orphan*/ * hwfns; } ;
struct TYPE_17__ {scalar_t__ callout_init; } ;
struct TYPE_18__ {int num_rss; int /*<<< orphan*/  qlnx_callout; TYPE_1__ flags; int /*<<< orphan*/  hw_stats; int /*<<< orphan*/  state; struct ecore_dev cdev; TYPE_13__* irq_vec; int /*<<< orphan*/  num_tc; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qlnx_host_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_16__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  handle; int /*<<< orphan*/  irq_rid; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  QLNX_STATE_OPEN ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  QL_DPRINT2 (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  bus_bind_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 
 int mp_ncpus ; 
 int qlnx_alloc_mem_arrays (TYPE_2__*) ; 
 int qlnx_alloc_mem_load (TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_fp_isr ; 
 int /*<<< orphan*/  qlnx_free_mem_load (TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_init_fp (TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_link_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_set_link (TYPE_2__*,int) ; 
 int qlnx_set_rx_mode (TYPE_2__*) ; 
 int qlnx_start_queues (TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_timer ; 
 scalar_t__ qlnx_vf_device (TYPE_2__*) ; 

__attribute__((used)) static int
qlnx_load(qlnx_host_t *ha)
{
	int			i;
	int			rc = 0;
	struct ecore_dev	*cdev;
        device_t		dev;

	cdev = &ha->cdev;
        dev = ha->pci_dev;

	QL_DPRINT2(ha, "enter\n");

        rc = qlnx_alloc_mem_arrays(ha);
        if (rc)
                goto qlnx_load_exit0;

        qlnx_init_fp(ha);

        rc = qlnx_alloc_mem_load(ha);
        if (rc)
                goto qlnx_load_exit1;

        QL_DPRINT2(ha, "Allocated %d RSS queues on %d TC/s\n",
		   ha->num_rss, ha->num_tc);

	for (i = 0; i < ha->num_rss; i++) {

		if ((rc = bus_setup_intr(dev, ha->irq_vec[i].irq,
                        (INTR_TYPE_NET | INTR_MPSAFE),
                        NULL, qlnx_fp_isr, &ha->irq_vec[i],
                        &ha->irq_vec[i].handle))) {

                        QL_DPRINT1(ha, "could not setup interrupt\n");
                        goto qlnx_load_exit2;
		}

		QL_DPRINT2(ha, "rss_id = %d irq_rid %d \
			 irq %p handle %p\n", i,
			ha->irq_vec[i].irq_rid,
			ha->irq_vec[i].irq, ha->irq_vec[i].handle);

		bus_bind_intr(dev, ha->irq_vec[i].irq, (i % mp_ncpus));
	}

        rc = qlnx_start_queues(ha);
        if (rc)
                goto qlnx_load_exit2;

        QL_DPRINT2(ha, "Start VPORT, RXQ and TXQ succeeded\n");

        /* Add primary mac and set Rx filters */
        rc = qlnx_set_rx_mode(ha);
        if (rc)
                goto qlnx_load_exit2;

        /* Ask for link-up using current configuration */
	qlnx_set_link(ha, true);

	if (qlnx_vf_device(ha) == 0)
		qlnx_link_update(&ha->cdev.hwfns[0]);

        ha->state = QLNX_STATE_OPEN;

	bzero(&ha->hw_stats, sizeof(struct ecore_eth_stats));

	if (ha->flags.callout_init)
        	callout_reset(&ha->qlnx_callout, hz, qlnx_timer, ha);

        goto qlnx_load_exit0;

qlnx_load_exit2:
        qlnx_free_mem_load(ha);

qlnx_load_exit1:
        ha->num_rss = 0;

qlnx_load_exit0:
	QL_DPRINT2(ha, "exit [%d]\n", rc);
        return rc;
}