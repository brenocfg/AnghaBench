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
struct fire_softc {int sc_flags; int sc_msiq_count; int sc_msi_count; int* sc_msi_msiq_table; int sc_msi_first; int /*<<< orphan*/  sc_msi_mtx; int /*<<< orphan*/  sc_msi_bitmap; int /*<<< orphan*/  sc_msiq_bitmap; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int FIRE_MSIX ; 
 struct fire_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fire_alloc_msix(device_t dev, device_t child, int *irq)
{
	struct fire_softc *sc;
	int i, msiq;

	sc = device_get_softc(dev);
	if ((sc->sc_flags & FIRE_MSIX) == 0)
		return (ENXIO);
	mtx_lock(&sc->sc_msi_mtx);
	msiq = 0;
	for (i = 0; i < sc->sc_msiq_count; i++) {
		if (isclr(sc->sc_msiq_bitmap, i) != 0) {
			msiq = i;
			break;
		}
	}
	if (i == sc->sc_msiq_count) {
		mtx_unlock(&sc->sc_msi_mtx);
		return (ENXIO);
	}
	for (i = sc->sc_msi_count - 1; i >= 0; i--) {
		if (isclr(sc->sc_msi_bitmap, i) != 0) {
			setbit(sc->sc_msiq_bitmap, msiq);
			setbit(sc->sc_msi_bitmap, i);
			sc->sc_msi_msiq_table[i] = msiq;
			*irq = sc->sc_msi_first + i;
			mtx_unlock(&sc->sc_msi_mtx);
			return (0);
		}
	}
	mtx_unlock(&sc->sc_msi_mtx);
	return (ENXIO);
}