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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
struct psycho_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_is; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  PSR_UE_AFA ; 
 int /*<<< orphan*/  PSR_UE_AFS ; 
 int PSYCHO_READ8 (struct psycho_softc*,int /*<<< orphan*/ ) ; 
 int UEAFSR_P_DTE ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_decode_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psycho_ue(void *arg)
{
	struct psycho_softc *sc = arg;
	uint64_t afar, afsr;

	afar = PSYCHO_READ8(sc, PSR_UE_AFA);
	afsr = PSYCHO_READ8(sc, PSR_UE_AFS);
	/*
	 * On the UltraSPARC-IIi/IIe, IOMMU misses/protection faults cause
	 * the AFAR to be set to the physical address of the TTE entry that
	 * was invalid/write protected.  Call into the IOMMU code to have
	 * them decoded to virtual I/O addresses.
	 */
	if ((afsr & UEAFSR_P_DTE) != 0)
		iommu_decode_fault(sc->sc_is, afar);
	panic("%s: uncorrectable DMA error AFAR %#lx AFSR %#lx",
	    device_get_nameunit(sc->sc_dev), (u_long)afar, (u_long)afsr);
	return (FILTER_HANDLED);
}