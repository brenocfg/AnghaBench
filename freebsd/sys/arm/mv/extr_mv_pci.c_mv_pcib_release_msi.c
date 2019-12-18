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
typedef  int u_int ;
struct mv_pcib_softc {int /*<<< orphan*/  sc_msi_mtx; int /*<<< orphan*/  sc_msi_bitmap; int /*<<< orphan*/  sc_msi_supported; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ MSI_IRQ ; 
 int /*<<< orphan*/  clrbit (int /*<<< orphan*/ *,scalar_t__) ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mv_pcib_release_msi(device_t dev, device_t child, int count, int *irqs)
{
	struct mv_pcib_softc *sc;
	u_int i;

	sc = device_get_softc(dev);
	if(!sc->sc_msi_supported)
		return (ENOTSUP);

	mtx_lock(&sc->sc_msi_mtx);

	for (i = 0; i < count; i++)
		clrbit(&sc->sc_msi_bitmap, irqs[i] - MSI_IRQ);

	mtx_unlock(&sc->sc_msi_mtx);
	return (0);
}