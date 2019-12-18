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
struct tws_softc {int intr_type; int irqs; int* irq_res_id; int /*<<< orphan*/  tws_dev; void** irq_res; } ;

/* Variables and functions */
 int FAILURE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
#define  TWS_INTx 129 
#define  TWS_MSI 128 
 int /*<<< orphan*/  TWS_TRACE (struct tws_softc*,char*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int tws_setup_intr (struct tws_softc*,int) ; 

__attribute__((used)) static int 
tws_setup_irq(struct tws_softc *sc)
{
    int messages;

    switch(sc->intr_type) {
        case TWS_INTx :
            sc->irqs = 1;
            sc->irq_res_id[0] = 0;
            sc->irq_res[0] = bus_alloc_resource_any(sc->tws_dev, SYS_RES_IRQ,
                            &sc->irq_res_id[0], RF_SHAREABLE | RF_ACTIVE);
            if ( ! sc->irq_res[0] )
                return(FAILURE);
            if ( tws_setup_intr(sc, sc->irqs) == FAILURE )
                return(FAILURE);
            device_printf(sc->tws_dev, "Using legacy INTx\n");
            break;
        case TWS_MSI :
            sc->irqs = 1;
            sc->irq_res_id[0] = 1;
            messages = 1;
            if (pci_alloc_msi(sc->tws_dev, &messages) != 0 ) {
                TWS_TRACE(sc, "pci alloc msi fail", 0, messages);
                return(FAILURE);
            }
            sc->irq_res[0] = bus_alloc_resource_any(sc->tws_dev, SYS_RES_IRQ,
                              &sc->irq_res_id[0], RF_SHAREABLE | RF_ACTIVE);
              
            if ( !sc->irq_res[0]  )
                return(FAILURE);
            if ( tws_setup_intr(sc, sc->irqs) == FAILURE )
                return(FAILURE);
            device_printf(sc->tws_dev, "Using MSI\n");
            break;

    }

    return(SUCCESS);
}