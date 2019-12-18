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
struct tws_softc {int /*<<< orphan*/ * intr_handle; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  tws_dev; } ;

/* Variables and functions */
 int FAILURE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  SETUP_INTR_RES ; 
 int SUCCESS ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tws_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_intr ; 
 int /*<<< orphan*/  tws_log (struct tws_softc*,int /*<<< orphan*/ ) ; 

int
tws_setup_intr(struct tws_softc *sc, int irqs)
{
    int i, error;

    for(i=0;i<irqs;i++) {
        if (!(sc->intr_handle[i])) {
            if ((error = bus_setup_intr(sc->tws_dev, sc->irq_res[i],
                                    INTR_TYPE_CAM | INTR_MPSAFE,
                                    NULL, 
                                    tws_intr, sc, &sc->intr_handle[i]))) {
                tws_log(sc, SETUP_INTR_RES);
                return(FAILURE);
            }
        }
    }
    return(SUCCESS);

}