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
struct adc_softc {int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CFG ; 
 int /*<<< orphan*/  ADC_GC ; 
 int /*<<< orphan*/  ADC_HC0 ; 
 int CFG_MODE_12 ; 
 int CFG_MODE_M ; 
 int CFG_MODE_S ; 
 int ENXIO ; 
 int GC_ADCO ; 
 int GC_AVGE ; 
 int HC_AIEN ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int READ4 (struct adc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct adc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adc_intr ; 
 struct adc_softc* adc_sc ; 
 int /*<<< orphan*/  adc_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct adc_softc*,int /*<<< orphan*/ *) ; 
 struct adc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adc_attach(device_t dev)
{
	struct adc_softc *sc;
	int err;
	int reg;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, adc_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	adc_sc = sc;

	/* Setup interrupt handler */
	err = bus_setup_intr(dev, sc->res[1], INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, adc_intr, sc, &sc->ih);
	if (err) {
		device_printf(dev, "Unable to alloc interrupt resource.\n");
		return (ENXIO);
	}

	/* Configure 12-bit mode */
	reg = READ4(sc, ADC_CFG);
	reg &= ~(CFG_MODE_M << CFG_MODE_S);
	reg |= (CFG_MODE_12 << CFG_MODE_S); /* 12bit */
	WRITE4(sc, ADC_CFG, reg);

	/* Configure for continuous conversion */
	reg = READ4(sc, ADC_GC);
	reg |= (GC_ADCO | GC_AVGE);
	WRITE4(sc, ADC_GC, reg);

	/* Disable interrupts */
	reg = READ4(sc, ADC_HC0);
	reg &= HC_AIEN;
	WRITE4(sc, ADC_HC0, reg);

	return (0);
}