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
struct ncr53c9x_softc {int dummy; } ;
struct esp_softc {int /*<<< orphan*/  sc_irqres; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_dma; int /*<<< orphan*/  sc_irq; struct ncr53c9x_softc sc_ncr53c9x; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR_LOCK_DESTROY (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsi64854_detach (int /*<<< orphan*/ ) ; 
 int ncr53c9x_detach (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
espdetach(struct esp_softc *esc)
{
	struct ncr53c9x_softc *sc = &esc->sc_ncr53c9x;
	int error;

	bus_teardown_intr(esc->sc_dev, esc->sc_irqres, esc->sc_irq);
	error = ncr53c9x_detach(sc);
	if (error != 0)
		return (error);
	error = lsi64854_detach(esc->sc_dma);
	if (error != 0)
		return (error);
	NCR_LOCK_DESTROY(sc);
	bus_release_resource(esc->sc_dev, SYS_RES_IRQ,
	    rman_get_rid(esc->sc_irqres), esc->sc_irqres);

	return (0);
}