#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct intr_irqsrc {int dummy; } ;
struct hirq {unsigned int irq; struct beripic_softc* sc; } ;
struct beripic_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  dev; TYPE_1__* irqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {struct intr_irqsrc isrc; } ;

/* Variables and functions */
 size_t BP_CFG ; 
 unsigned int BP_CFG_ENABLE ; 
 unsigned int BP_CFG_IRQ_M ; 
 size_t BP_IP_CLEAR ; 
 size_t BP_IP_READ ; 
 int FILTER_HANDLED ; 
 unsigned int bus_read_8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int fls (unsigned int) ; 
 scalar_t__ intr_isrc_dispatch (struct intr_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_pic_intr(void *arg)
{
	struct beripic_softc *sc;
	struct intr_irqsrc *isrc;
	struct hirq *h;
	uint64_t intr;
	uint64_t reg;
	int i;

	h = arg;
	sc = h->sc;

	intr = bus_read_8(sc->res[BP_IP_READ], 0);
	while ((i = fls(intr)) != 0) {
		i--;
		intr &= ~(1u << i);

		isrc = &sc->irqs[i].isrc;

		reg = bus_read_8(sc->res[BP_CFG], i * 8);
		if ((reg & BP_CFG_IRQ_M) != h->irq) {
			continue;
		}
		if ((reg & (BP_CFG_ENABLE)) == 0) {
			continue;
		}

		if (intr_isrc_dispatch(isrc, curthread->td_intr_frame) != 0) {
			device_printf(sc->dev, "Stray interrupt %u detected\n", i);
		}

		bus_write_8(sc->res[BP_IP_CLEAR], 0, (1 << i));
	}

	return (FILTER_HANDLED);
}