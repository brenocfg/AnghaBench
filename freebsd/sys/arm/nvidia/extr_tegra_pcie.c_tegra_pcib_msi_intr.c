#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct trapframe {int dummy; } ;
struct tegra_pcib_softc {int /*<<< orphan*/  dev; struct tegra_pcib_irqsrc* isrcs; } ;
struct tegra_pcib_irqsrc {int /*<<< orphan*/  isrc; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 scalar_t__ AFI_MSI_INTR_IN_REG ; 
 scalar_t__ AFI_MSI_REGS ; 
 int /*<<< orphan*/  AFI_MSI_VEC (scalar_t__) ; 
 scalar_t__ AFI_RD4 (struct tegra_pcib_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFI_WR4 (struct tegra_pcib_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_HANDLED ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ffs (scalar_t__) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,struct trapframe*) ; 
 int /*<<< orphan*/  tegra_pcib_isrc_mask (struct tegra_pcib_softc*,struct tegra_pcib_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_pcib_msi_intr(void *arg)
{
	u_int irq, i, bit, reg;
	struct tegra_pcib_softc *sc;
	struct trapframe *tf;
	struct tegra_pcib_irqsrc *tgi;

	sc = (struct tegra_pcib_softc *)arg;
	tf = curthread->td_intr_frame;

	for (i = 0; i < AFI_MSI_REGS; i++) {
		reg = AFI_RD4(sc, AFI_MSI_VEC(i));
		/* Handle one vector. */
		while (reg != 0) {
			bit = ffs(reg) - 1;
			/* Send EOI */
			AFI_WR4(sc, AFI_MSI_VEC(i), 1 << bit);
			irq = i * AFI_MSI_INTR_IN_REG + bit;
			tgi = &sc->isrcs[irq];
			if (intr_isrc_dispatch(&tgi->isrc, tf) != 0) {
				/* Disable stray. */
				tegra_pcib_isrc_mask(sc, tgi, 0);
				device_printf(sc->dev,
				    "Stray irq %u disabled\n", irq);
			}
			reg = AFI_RD4(sc, AFI_MSI_VEC(i));
		}
	}
	return (FILTER_HANDLED);
}