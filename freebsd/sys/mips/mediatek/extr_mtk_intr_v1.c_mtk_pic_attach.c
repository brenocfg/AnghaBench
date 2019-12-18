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
struct mtk_pic_softc {int /*<<< orphan*/ * pic_res; int /*<<< orphan*/  pic_intrhand; int /*<<< orphan*/  pic_irqs; int /*<<< orphan*/  nirqs; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pic_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  MTK_INTDIS ; 
 int /*<<< orphan*/  MTK_INTENA ; 
 int /*<<< orphan*/  MTK_INTTYPE ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  WRITE4 (struct mtk_pic_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_pic_softc*,int /*<<< orphan*/ *) ; 
 struct mtk_pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  mtk_pic_intr ; 
 scalar_t__ mtk_pic_register_isrcs (struct mtk_pic_softc*) ; 
 int /*<<< orphan*/  mtk_pic_spec ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 intptr_t pic_xref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pic_attach(device_t dev)
{
	struct mtk_pic_softc *sc;
	intptr_t xref = pic_xref(dev);

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, mtk_pic_spec, sc->pic_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->pic_dev = dev;

	/* Initialize mutex */
	mtx_init(&sc->mutex, "PIC lock", "", MTX_SPIN);

	/* Set the number of interrupts */
	sc->nirqs = nitems(sc->pic_irqs);

	/* Mask all interrupts */
	WRITE4(sc, MTK_INTDIS, 0x7FFFFFFF);

	/* But enable interrupt generation/masking */
	WRITE4(sc, MTK_INTENA, 0x80000000);

	/* Set all interrupts to type 0 */
	WRITE4(sc, MTK_INTTYPE, 0x00000000);

	/* Register the interrupts */
	if (mtk_pic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register PIC ISRCs\n");
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

	if (bus_setup_intr(dev, sc->pic_res[1], INTR_TYPE_CLK,
	    mtk_pic_intr, NULL, sc, &sc->pic_intrhand)) {
		device_printf(dev, "could not setup irq handler\n");
		intr_pic_deregister(dev, xref);
		goto cleanup;
	}
	return (0);

cleanup:
	bus_release_resources(dev, mtk_pic_spec, sc->pic_res);
	return(ENXIO);
}