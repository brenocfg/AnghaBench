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
typedef  unsigned int uint32_t ;
struct thread {int /*<<< orphan*/  td_intr_nesting_level; int /*<<< orphan*/  td_intr_frame; } ;
struct mtk_gic_softc {int /*<<< orphan*/  gic_dev; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  GIC_INTR_ISRC (struct mtk_gic_softc*,unsigned int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTK_INTMASK ; 
 int /*<<< orphan*/  MTK_INTSTAT ; 
 unsigned int READ4 (struct mtk_gic_softc*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int fls (unsigned int) ; 
 int /*<<< orphan*/  gic_irq_mask (struct mtk_gic_softc*,unsigned int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_gic_intr(void *arg)
{
	struct mtk_gic_softc *sc = arg;
	struct thread *td;
	uint32_t i, intr;

	td = curthread;
	/* Workaround: do not inflate intr nesting level */
	td->td_intr_nesting_level--;

	intr = READ4(sc, MTK_INTSTAT) & READ4(sc, MTK_INTMASK);
	while ((i = fls(intr)) != 0) {
		i--;
		intr &= ~(1u << i);

		if (intr_isrc_dispatch(GIC_INTR_ISRC(sc, i),
		    curthread->td_intr_frame) != 0) {
			device_printf(sc->gic_dev,
				"Stray interrupt %u detected\n", i);
			gic_irq_mask(sc, i);
			continue;
		}
	}

	KASSERT(i == 0, ("all interrupts handled"));

	td->td_intr_nesting_level++;

	return (FILTER_HANDLED);
}