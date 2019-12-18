#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lg_base; int ndelta; int lg_delta; scalar_t__ psz; } ;
typedef  TYPE_1__ sc_t ;
struct TYPE_5__ {int large_maxclass; TYPE_1__* sc; } ;
typedef  TYPE_2__ sc_data_t ;

/* Variables and functions */
 int PAGE ; 
 scalar_t__ SC_NPSIZES ; 
 unsigned int SC_NSIZES ; 
 int ZU (int) ; 
 int* sz_pind2sz_tab ; 

__attribute__((used)) static void
sz_boot_pind2sz_tab(const sc_data_t *sc_data) {
	int pind = 0;
	for (unsigned i = 0; i < SC_NSIZES; i++) {
		const sc_t *sc = &sc_data->sc[i];
		if (sc->psz) {
			sz_pind2sz_tab[pind] = (ZU(1) << sc->lg_base)
			    + (ZU(sc->ndelta) << sc->lg_delta);
			pind++;
		}
	}
	for (int i = pind; i <= (int)SC_NPSIZES; i++) {
		sz_pind2sz_tab[pind] = sc_data->large_maxclass + PAGE;
	}
}