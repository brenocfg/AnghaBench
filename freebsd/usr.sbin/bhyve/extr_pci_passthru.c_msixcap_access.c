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
struct TYPE_2__ {int capoff; } ;
struct passthru_softc {TYPE_1__ psc_msix; } ;

/* Variables and functions */
 int MSIX_CAPLEN ; 

__attribute__((used)) static int 
msixcap_access(struct passthru_softc *sc, int coff)
{
	if (sc->psc_msix.capoff == 0) 
		return (0);

	return (coff >= sc->psc_msix.capoff && 
	        coff < sc->psc_msix.capoff + MSIX_CAPLEN);
}