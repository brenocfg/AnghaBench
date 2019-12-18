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
struct TYPE_2__ {int /*<<< orphan*/  irq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 struct cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpcht_release_msix(device_t dev, device_t child, int irq)
{
	struct cpcht_softc *sc;

	sc = device_get_softc(dev);

	mtx_lock(&sc->htirq_mtx);
	sc->htirq_map[irq & 0xff].irq_type = IRQ_NONE;
	mtx_unlock(&sc->htirq_mtx);

	return (0);
}