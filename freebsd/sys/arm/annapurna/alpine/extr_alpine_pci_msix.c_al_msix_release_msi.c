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
struct intr_irqsrc {int dummy; } ;
struct al_msix_softc {int /*<<< orphan*/  msi_mtx; int /*<<< orphan*/ ** isrcs; int /*<<< orphan*/  irq_alloc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ERR_NOT_IN_MAP ; 
 int al_find_intr_pos_in_map (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 struct al_msix_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
al_msix_release_msi(device_t dev, device_t child, int count,
    struct intr_irqsrc **srcs)
{
	struct al_msix_softc *sc;
	int i, pos;

	sc = device_get_softc(dev);

	mtx_lock(&sc->msi_mtx);

	pos = al_find_intr_pos_in_map(dev, *srcs);
	vmem_free(sc->irq_alloc, pos, count);
	for (i = 0; i < count; i++) {
		pos = al_find_intr_pos_in_map(dev, *srcs);
		if (pos != ERR_NOT_IN_MAP)
			sc->isrcs[pos] = NULL;
		srcs++;
	}

	mtx_unlock(&sc->msi_mtx);

	return (0);
}