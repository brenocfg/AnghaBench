#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_pruss_softc {TYPE_4__* sc_irq_devs; TYPE_1__* sc_pdev; } ;
typedef  size_t int8_t ;
struct TYPE_11__ {TYPE_4__* si_drv1; } ;
struct TYPE_8__ {scalar_t__ idx; } ;
struct TYPE_9__ {TYPE_2__ ctl; } ;
struct TYPE_10__ {int channel; int event; int enable; TYPE_3__ tstamps; TYPE_5__* sc_pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  PRUSS_INTC_EICR ; 
 int /*<<< orphan*/  PRUSS_INTC_EISR ; 
 int /*<<< orphan*/  PRUSS_INTC_HIDISR ; 
 int /*<<< orphan*/  PRUSS_INTC_HIEISR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (TYPE_5__*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ti_pruss_cdevirq ; 
 int /*<<< orphan*/  ti_pruss_reg_write (struct ti_pruss_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline int
ti_pruss_interrupts_enable(struct ti_pruss_softc *sc, int8_t irq, bool enable)
{
	if (enable && ((sc->sc_irq_devs[irq].channel == -1) ||
	    (sc->sc_irq_devs[irq].event== -1)))
	{
		device_printf( sc->sc_pdev->si_drv1,
			"Interrupt chain not fully configured, not possible to enable\n" );
		return (EINVAL);
	}

	sc->sc_irq_devs[irq].enable = enable;

	if (sc->sc_irq_devs[irq].sc_pdev) {
		destroy_dev(sc->sc_irq_devs[irq].sc_pdev);
		sc->sc_irq_devs[irq].sc_pdev = NULL;
	}

	if (enable) {
		sc->sc_irq_devs[irq].sc_pdev = make_dev(&ti_pruss_cdevirq, 0, UID_ROOT, GID_WHEEL,
		    0600, "pruss%d.irq%d", device_get_unit(sc->sc_pdev->si_drv1), irq);
		sc->sc_irq_devs[irq].sc_pdev->si_drv1 = &sc->sc_irq_devs[irq];

		sc->sc_irq_devs[irq].tstamps.ctl.idx = 0;
	}

	uint32_t reg = enable ? PRUSS_INTC_HIEISR : PRUSS_INTC_HIDISR;
	ti_pruss_reg_write(sc, reg, sc->sc_irq_devs[irq].channel);

	reg = enable ? PRUSS_INTC_EISR : PRUSS_INTC_EICR;
	ti_pruss_reg_write(sc, reg, sc->sc_irq_devs[irq].event );

	return (0);
}