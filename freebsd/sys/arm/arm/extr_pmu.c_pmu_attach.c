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
struct pmu_softc {int /*<<< orphan*/ * ih; int /*<<< orphan*/ ** res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int MAXCPU ; 
 int MAX_RLEN ; 
 int /*<<< orphan*/  PMU_IESR_C ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__* ccnt_hi ; 
 int /*<<< orphan*/  cp15_pminten_get () ; 
 int /*<<< orphan*/  cp15_pminten_set (int /*<<< orphan*/ ) ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pmu_attched ; 
 int /*<<< orphan*/  pmu_intr ; 
 int /*<<< orphan*/  pmu_spec ; 

__attribute__((used)) static int
pmu_attach(device_t dev)
{
	struct pmu_softc *sc;
#if defined(__arm__) && (__ARM_ARCH > 6)
	uint32_t iesr;
#endif
	int err;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, pmu_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Setup interrupt handler */
	for (i = 0; i < MAX_RLEN; i++) {
		if (sc->res[i] == NULL)
			break;

		err = bus_setup_intr(dev, sc->res[i], INTR_MPSAFE | INTR_TYPE_MISC,
		    pmu_intr, NULL, NULL, &sc->ih[i]);
		if (err) {
			device_printf(dev, "Unable to setup interrupt handler.\n");
			return (ENXIO);
		}
	}

#if defined(__arm__) && (__ARM_ARCH > 6)
	/* Initialize to 0. */
	for (i = 0; i < MAXCPU; i++)
		ccnt_hi[i] = 0;

	/* Enable the interrupt to fire on overflow. */
	iesr = cp15_pminten_get();
	iesr |= PMU_IESR_C;
	cp15_pminten_set(iesr);

	/* Need this for getcyclecount() fast path. */
	pmu_attched |= 1;
#endif

	return (0);
}