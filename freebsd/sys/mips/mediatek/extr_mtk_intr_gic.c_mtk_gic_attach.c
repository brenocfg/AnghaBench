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
struct mtk_gic_softc {int /*<<< orphan*/  gic_res; int /*<<< orphan*/  gic_irqs; int /*<<< orphan*/  nirqs; int /*<<< orphan*/  mutex; int /*<<< orphan*/  gic_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  MTK_INTDIS ; 
 int /*<<< orphan*/  MTK_INTPOL ; 
 int /*<<< orphan*/  MTK_INTTRIG ; 
 int /*<<< orphan*/  MTK_MAPPIN (int) ; 
 int /*<<< orphan*/  MTK_MAPVPE (int,int /*<<< orphan*/ ) ; 
 int MTK_PIN_BITS (int /*<<< orphan*/ ) ; 
 int MTK_VPE_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  WRITE4 (struct mtk_gic_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_establish_hardintr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_gic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mtk_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 intptr_t gic_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  mtk_gic_intr ; 
 scalar_t__ mtk_gic_register_isrcs (struct mtk_gic_softc*) ; 
 int /*<<< orphan*/  mtk_gic_spec ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_gic_attach(device_t dev)
{
	struct mtk_gic_softc *sc;
	intptr_t xref = gic_xref(dev);
	int i;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, mtk_gic_spec, sc->gic_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->gic_dev = dev;

	/* Initialize mutex */
	mtx_init(&sc->mutex, "PIC lock", "", MTX_SPIN);

	/* Set the number of interrupts */
	sc->nirqs = nitems(sc->gic_irqs);

	/* Mask all interrupts */
	WRITE4(sc, MTK_INTDIS, 0xFFFFFFFF);

	/* All interrupts are of type level */
	WRITE4(sc, MTK_INTTRIG, 0x00000000);

	/* All interrupts are of positive polarity */
	WRITE4(sc, MTK_INTPOL, 0xFFFFFFFF);

	/*
	 * Route all interrupts to pin 0 on VPE 0;
	 */
	for (i = 0; i < 32; i++) {
		WRITE4(sc, MTK_MAPPIN(i), MTK_PIN_BITS(0));
		WRITE4(sc, MTK_MAPVPE(i, 0), MTK_VPE_BITS(0));
	}

	/* Register the interrupts */
	if (mtk_gic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register GIC ISRCs\n");
		goto cleanup;
	}

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto cleanup;
	}

	cpu_establish_hardintr("gic", mtk_gic_intr, NULL, sc, 0, INTR_TYPE_CLK,
	    NULL);

	return (0);

cleanup:
	bus_release_resources(dev, mtk_gic_spec, sc->gic_res);
	return(ENXIO);
}