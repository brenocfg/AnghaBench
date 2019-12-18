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
struct host1x_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * syncpt_irq_res; int /*<<< orphan*/ * gen_irq_res; int /*<<< orphan*/ * syncpt_irq_h; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * tegra_drm; int /*<<< orphan*/ * gen_irq_h; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct host1x_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct host1x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_drm_exit (struct host1x_softc*) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
host1x_detach(device_t dev)
{
	struct host1x_softc *sc;

	sc = device_get_softc(dev);

	host1x_drm_exit(sc);

	if (sc->gen_irq_h != NULL)
		bus_teardown_intr(dev, sc->gen_irq_res, sc->gen_irq_h);
	if (sc->tegra_drm != NULL)
		free(sc->tegra_drm, DRM_MEM_DRIVER);
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (sc->reset != NULL)
		hwreset_release(sc->reset);
	if (sc->syncpt_irq_h != NULL)
		bus_teardown_intr(dev, sc->syncpt_irq_res, sc->syncpt_irq_h);
	if (sc->gen_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 1, sc->gen_irq_res);
	if (sc->syncpt_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->syncpt_irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	LOCK_DESTROY(sc);
	return (bus_generic_detach(dev));
}