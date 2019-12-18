#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int index; int lg_base; int lg_delta; int ndelta; int psz; int bin; int lg_delta_lookup; scalar_t__ pgs; } ;
typedef  TYPE_1__ sc_t ;

/* Variables and functions */
 int ZU (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int reg_size_compute (int,int,int) ; 
 scalar_t__ slab_size (int,int,int,int) ; 

__attribute__((used)) static void
size_class(
    /* Output. */
    sc_t *sc,
    /* Configuration decisions. */
    int lg_max_lookup, int lg_page, int lg_ngroup,
    /* Inputs specific to the size class. */
    int index, int lg_base, int lg_delta, int ndelta) {
	sc->index = index;
	sc->lg_base = lg_base;
	sc->lg_delta = lg_delta;
	sc->ndelta = ndelta;
	sc->psz = (reg_size_compute(lg_base, lg_delta, ndelta)
	    % (ZU(1) << lg_page) == 0);
	size_t size = (ZU(1) << lg_base) + (ZU(ndelta) << lg_delta);
	if (index == 0) {
		assert(!sc->psz);
	}
	if (size < (ZU(1) << (lg_page + lg_ngroup))) {
		sc->bin = true;
		sc->pgs = slab_size(lg_page, lg_base, lg_delta, ndelta);
	} else {
		sc->bin = false;
		sc->pgs = 0;
	}
	if (size <= (ZU(1) << lg_max_lookup)) {
		sc->lg_delta_lookup = lg_delta;
	} else {
		sc->lg_delta_lookup = 0;
	}
}