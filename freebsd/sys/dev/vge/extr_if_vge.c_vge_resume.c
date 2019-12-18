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
typedef  int uint16_t ;
struct vge_softc {int vge_flags; struct ifnet* vge_ifp; scalar_t__ vge_pmcap; int /*<<< orphan*/  vge_dev; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int VGE_FLAG_PMCAP ; 
 int VGE_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  vge_clrwol (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_init_locked (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_miipoll_start (struct vge_softc*) ; 

__attribute__((used)) static int
vge_resume(device_t dev)
{
	struct vge_softc *sc;
	struct ifnet *ifp;
	uint16_t pmstat;

	sc = device_get_softc(dev);
	VGE_LOCK(sc);
	if ((sc->vge_flags & VGE_FLAG_PMCAP) != 0) {
		/* Disable PME and clear PME status. */
		pmstat = pci_read_config(sc->vge_dev,
		    sc->vge_pmcap + PCIR_POWER_STATUS, 2);
		if ((pmstat & PCIM_PSTAT_PMEENABLE) != 0) {
			pmstat &= ~PCIM_PSTAT_PMEENABLE;
			pci_write_config(sc->vge_dev,
			    sc->vge_pmcap + PCIR_POWER_STATUS, pmstat, 2);
		}
	}
	vge_clrwol(sc);
	/* Restart MII auto-polling. */
	vge_miipoll_start(sc);
	ifp = sc->vge_ifp;
	/* Reinitialize interface if necessary. */
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		vge_init_locked(sc);
	}
	sc->vge_flags &= ~VGE_FLAG_SUSPENDED;
	VGE_UNLOCK(sc);

	return (0);
}