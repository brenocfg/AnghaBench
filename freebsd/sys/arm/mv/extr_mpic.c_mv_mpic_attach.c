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
typedef  int /*<<< orphan*/  uint32_t ;
struct mv_mpic_softc {int /*<<< orphan*/ ** mpic_res; int /*<<< orphan*/  nirqs; void* drbl_bsh; void* drbl_bst; void* cpu_bsh; void* cpu_bst; void* mpic_bsh; void* mpic_bst; int /*<<< orphan*/  intr_hand; int /*<<< orphan*/  mtx; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 scalar_t__ MPIC_CPU (int) ; 
 int MPIC_CPU_READ (struct mv_mpic_softc*,scalar_t__) ; 
 int /*<<< orphan*/  MPIC_CPU_WRITE (struct mv_mpic_softc*,scalar_t__,int) ; 
 scalar_t__ MPIC_CTP ; 
 int /*<<< orphan*/  MPIC_CTRL ; 
 int /*<<< orphan*/  MPIC_CTRL_NIRQS (int /*<<< orphan*/ ) ; 
 scalar_t__ MPIC_LOCAL_MASK ; 
 int /*<<< orphan*/  MPIC_READ (struct mv_mpic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPIC_WRITE (struct mv_mpic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mv_mpic_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mpic_intr ; 
 int /*<<< orphan*/  mpic_unmask_msi () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_mpic_register_isrcs (struct mv_mpic_softc*) ; 
 struct mv_mpic_softc* mv_mpic_sc ; 
 int /*<<< orphan*/  mv_mpic_spec ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mv_mpic_attach(device_t dev)
{
	struct mv_mpic_softc *sc;
	int error;
	uint32_t val;
	int cpu;

	sc = (struct mv_mpic_softc *)device_get_softc(dev);

	if (mv_mpic_sc != NULL)
		return (ENXIO);
	mv_mpic_sc = sc;

	sc->sc_dev = dev;

	mtx_init(&sc->mtx, "MPIC lock", NULL, MTX_SPIN);

	error = bus_alloc_resources(dev, mv_mpic_spec, sc->mpic_res);
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}
	if (sc->mpic_res[3] == NULL)
		device_printf(dev, "No interrupt to use.\n");
	else
		bus_setup_intr(dev, sc->mpic_res[3], INTR_TYPE_CLK,
		    mpic_intr, NULL, sc, &sc->intr_hand);

	sc->mpic_bst = rman_get_bustag(sc->mpic_res[0]);
	sc->mpic_bsh = rman_get_bushandle(sc->mpic_res[0]);

	sc->cpu_bst = rman_get_bustag(sc->mpic_res[1]);
	sc->cpu_bsh = rman_get_bushandle(sc->mpic_res[1]);

	if (sc->mpic_res[2] != NULL) {
		/* This is required only if MSIs are used. */
		sc->drbl_bst = rman_get_bustag(sc->mpic_res[2]);
		sc->drbl_bsh = rman_get_bushandle(sc->mpic_res[2]);
	}

	MPIC_WRITE(mv_mpic_sc, MPIC_CTRL, 1);
	MPIC_CPU_WRITE(mv_mpic_sc, MPIC_CTP, 0);

	val = MPIC_READ(mv_mpic_sc, MPIC_CTRL);
	sc->nirqs = MPIC_CTRL_NIRQS(val);

	if (mv_mpic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register PIC ISRCs\n");
		bus_release_resources(dev, mv_mpic_spec, sc->mpic_res);
		return (ENXIO);
	}

	OF_device_register_xref(OF_xref_from_node(ofw_bus_get_node(dev)), dev);

	if (intr_pic_register(dev, OF_xref_from_device(dev)) == NULL) {
		device_printf(dev, "could not register PIC\n");
		bus_release_resources(dev, mv_mpic_spec, sc->mpic_res);
		return (ENXIO);
	}

	mpic_unmask_msi();

	/* Unmask CPU performance counters overflow irq */
	for (cpu = 0; cpu < mp_ncpus; cpu++)
		MPIC_CPU_WRITE(mv_mpic_sc, MPIC_CPU(cpu) + MPIC_LOCAL_MASK,
		    (1 << cpu) | MPIC_CPU_READ(mv_mpic_sc,
		    MPIC_CPU(cpu) + MPIC_LOCAL_MASK));

	return (0);
}