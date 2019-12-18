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
typedef  size_t uint16_t ;
struct amd_ntb_softc {TYPE_1__* int_info; struct amd_ntb_softc* msix_vec; int /*<<< orphan*/  device; int /*<<< orphan*/  allocated_interrupts; } ;
struct TYPE_2__ {size_t rid; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  amd_ntb_irq_isr ; 
 int /*<<< orphan*/  amd_ntb_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  amd_ntb_vec_isr ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct amd_ntb_softc*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
amd_ntb_setup_isr(struct amd_ntb_softc *ntb, uint16_t num_vectors, bool msi,
    bool intx)
{
	uint16_t i;
	int flags = 0, rc = 0;

	flags |= RF_ACTIVE;
	if (intx)
		flags |= RF_SHAREABLE;

	for (i = 0; i < num_vectors; i++) {

		/* RID should be 0 for intx */
		if (intx)
			ntb->int_info[i].rid = i;
		else
			ntb->int_info[i].rid = i + 1;

		ntb->int_info[i].res = bus_alloc_resource_any(ntb->device,
		    SYS_RES_IRQ, &ntb->int_info[i].rid, flags);
		if (ntb->int_info[i].res == NULL) {
			amd_ntb_printf(0, "bus_alloc_resource IRQ failed\n");
			return (ENOMEM);
		}

		ntb->int_info[i].tag = NULL;
		ntb->allocated_interrupts++;

		if (msi || intx) {
			rc = bus_setup_intr(ntb->device, ntb->int_info[i].res,
			    INTR_MPSAFE | INTR_TYPE_MISC, NULL, amd_ntb_irq_isr,
			    ntb, &ntb->int_info[i].tag);
		} else {
			rc = bus_setup_intr(ntb->device, ntb->int_info[i].res,
			    INTR_MPSAFE | INTR_TYPE_MISC, NULL, amd_ntb_vec_isr,
			    &ntb->msix_vec[i], &ntb->int_info[i].tag);
		}

		if (rc != 0) {
			amd_ntb_printf(0, "bus_setup_intr %d failed\n", i);
			return (ENXIO);
		}
	}

	return (0);
}