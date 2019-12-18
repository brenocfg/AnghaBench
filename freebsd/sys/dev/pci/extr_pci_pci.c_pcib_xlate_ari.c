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
struct pcib_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCIB_ENABLE_ARI ; 
 int PCIE_ARI_FUNC (int) ; 
 int PCIE_ARI_SLOT (int) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
pcib_xlate_ari(device_t pcib, int bus, int *slot, int *func)
{
	struct pcib_softc *sc;
	int ari_func;

	sc = device_get_softc(pcib);
	ari_func = *func;

	if (sc->flags & PCIB_ENABLE_ARI) {
		KASSERT(*slot == 0,
		    ("Non-zero slot number with ARI enabled!"));
		*slot = PCIE_ARI_SLOT(ari_func);
		*func = PCIE_ARI_FUNC(ari_func);
	}
}