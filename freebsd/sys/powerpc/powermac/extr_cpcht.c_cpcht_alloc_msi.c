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
struct cpcht_softc {int /*<<< orphan*/  htirq_mtx; TYPE_1__* htirq_map; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ irq_type; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IRQ_MSI ; 
 scalar_t__ IRQ_NONE ; 
 int MAP_IRQ (scalar_t__,int) ; 
 scalar_t__ cpcht_msipic ; 
 struct cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpcht_alloc_msi(device_t dev, device_t child, int count, int maxcount,
    int *irqs)
{
	struct cpcht_softc *sc;
	int i, j;

	sc = device_get_softc(dev);
	j = 0;

	/* Bail if no MSI PIC yet */
	if (cpcht_msipic == 0)
		return (ENXIO);

	mtx_lock(&sc->htirq_mtx);
	for (i = 8; i < 124 - count; i++) {
		for (j = 0; j < count; j++) {
			if (sc->htirq_map[i+j].irq_type != IRQ_NONE)
				break;
		}
		if (j == count)
			break;

		i += j; /* We know there isn't a large enough run */
	}

	if (j != count) {
		mtx_unlock(&sc->htirq_mtx);
		return (ENXIO);
	}

	for (j = 0; j < count; j++) {
		irqs[j] = MAP_IRQ(cpcht_msipic, i+j);
		sc->htirq_map[i+j].irq_type = IRQ_MSI;
	}
	mtx_unlock(&sc->htirq_mtx);

	return (0);
}