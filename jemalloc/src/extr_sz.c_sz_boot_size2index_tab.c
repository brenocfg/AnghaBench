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
struct TYPE_4__ {int lg_base; int ndelta; int lg_delta; } ;
typedef  TYPE_1__ sc_t ;
struct TYPE_5__ {TYPE_1__* sc; } ;
typedef  TYPE_2__ sc_data_t ;

/* Variables and functions */
 int SC_LG_TINY_MIN ; 
 int SC_LOOKUP_MAXCLASS ; 
 unsigned int SC_NSIZES ; 
 int ZU (int) ; 
 unsigned int* sz_size2index_tab ; 

__attribute__((used)) static void
sz_boot_size2index_tab(const sc_data_t *sc_data) {
	size_t dst_max = (SC_LOOKUP_MAXCLASS >> SC_LG_TINY_MIN) + 1;
	size_t dst_ind = 0;
	for (unsigned sc_ind = 0; sc_ind < SC_NSIZES && dst_ind < dst_max;
	    sc_ind++) {
		const sc_t *sc = &sc_data->sc[sc_ind];
		size_t sz = (ZU(1) << sc->lg_base)
		    + (ZU(sc->ndelta) << sc->lg_delta);
		size_t max_ind = ((sz + (ZU(1) << SC_LG_TINY_MIN) - 1)
				   >> SC_LG_TINY_MIN);
		for (; dst_ind <= max_ind && dst_ind < dst_max; dst_ind++) {
			sz_size2index_tab[dst_ind] = sc_ind;
		}
	}
}