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
typedef  scalar_t__ uint32_t ;
struct mv_ic_softc {int ic_high_regs; int ic_error_regs; int /*<<< orphan*/ * ic_res; int /*<<< orphan*/  ic_bsh; int /*<<< orphan*/  ic_bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ MV_DEV_88F6281 ; 
 scalar_t__ MV_DEV_88F6282 ; 
 scalar_t__ MV_DEV_MV78100 ; 
 scalar_t__ MV_DEV_MV78100_Z0 ; 
 int /*<<< orphan*/  arm_mask_irq_all () ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct mv_ic_softc* mv_ic_sc ; 
 int /*<<< orphan*/  mv_ic_spec ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_id (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
mv_ic_attach(device_t dev)
{
	struct mv_ic_softc *sc;
	uint32_t dev_id, rev_id;
	int error;

	sc = (struct mv_ic_softc *)device_get_softc(dev);

	if (mv_ic_sc != NULL)
		return (ENXIO);
	mv_ic_sc = sc;

	soc_id(&dev_id, &rev_id);

	sc->ic_high_regs = 0;
	sc->ic_error_regs = 0;

	if (dev_id == MV_DEV_88F6281 ||
	    dev_id == MV_DEV_88F6282 ||
	    dev_id == MV_DEV_MV78100 ||
	    dev_id == MV_DEV_MV78100_Z0)
		sc->ic_high_regs = 1;

	if (dev_id == MV_DEV_MV78100 || dev_id == MV_DEV_MV78100_Z0)
		sc->ic_error_regs = 1;

	error = bus_alloc_resources(dev, mv_ic_spec, sc->ic_res);
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->ic_bst = rman_get_bustag(sc->ic_res[0]);
	sc->ic_bsh = rman_get_bushandle(sc->ic_res[0]);

	/* Mask all interrupts */
	arm_mask_irq_all();

	return (0);
}