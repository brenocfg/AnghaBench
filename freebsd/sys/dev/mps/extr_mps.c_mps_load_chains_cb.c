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
struct mps_softc {scalar_t__ reqframesz; int chain_free_lowwater; scalar_t__ chain_frames; struct mps_chain* chains; } ;
struct mps_chain {scalar_t__ chain_busaddr; int /*<<< orphan*/ * chain; } ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  MPI2_SGE_IO_UNION ;

/* Variables and functions */
 int /*<<< orphan*/  mps_free_chain (struct mps_softc*,struct mps_chain*) ; 

__attribute__((used)) static void
mps_load_chains_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct mps_softc *sc = arg;
	struct mps_chain *chain;
	bus_size_t bo;
	int i, o, s;

	if (error != 0)
		return;

	for (i = 0, o = 0, s = 0; s < nsegs; s++) {
		for (bo = 0; bo + sc->reqframesz <= segs[s].ds_len;
		    bo += sc->reqframesz) {
			chain = &sc->chains[i++];
			chain->chain =(MPI2_SGE_IO_UNION *)(sc->chain_frames+o);
			chain->chain_busaddr = segs[s].ds_addr + bo;
			o += sc->reqframesz;
			mps_free_chain(sc, chain);
		}
		if (bo != segs[s].ds_len)
			o += segs[s].ds_len - bo;
	}
	sc->chain_free_lowwater = i;
}