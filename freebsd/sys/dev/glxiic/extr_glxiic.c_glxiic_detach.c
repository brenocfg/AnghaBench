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
struct glxiic_softc {int /*<<< orphan*/  old_irq; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ * irq_handler; int /*<<< orphan*/ * gpio_res; int /*<<< orphan*/  gpio_rid; int /*<<< orphan*/ * smb_res; int /*<<< orphan*/  smb_rid; int /*<<< orphan*/  callout; int /*<<< orphan*/ * iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_LOCK_DESTROY (struct glxiic_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct glxiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_gpio_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_smb_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_smb_map_interrupt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glxiic_detach(device_t dev)
{
	struct glxiic_softc *sc;
	int error;

	sc = device_get_softc(dev);

	error = bus_generic_detach(dev);
	if (error != 0)
		goto out;
	if (sc->iicbus != NULL)
		error = device_delete_child(dev, sc->iicbus);

out:
	callout_drain(&sc->callout);

	if (sc->smb_res != NULL) {
		glxiic_smb_disable(sc);
		bus_release_resource(dev, SYS_RES_IOPORT, sc->smb_rid,
		    sc->smb_res);
	}
	if (sc->gpio_res != NULL) {
		glxiic_gpio_disable(sc);
		bus_release_resource(dev, SYS_RES_IOPORT, sc->gpio_rid,
		    sc->gpio_res);
	}
	if (sc->irq_handler != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_handler);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irq_rid,
		    sc->irq_res);

	/* Restore the old SMBus interrupt mapping. */
	glxiic_smb_map_interrupt(sc->old_irq);

	GLXIIC_LOCK_DESTROY(sc);

	return (error);
}