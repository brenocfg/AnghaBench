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
struct hifn_softc {struct hifn_dma* sc_dma; } ;
struct hifn_dma {TYPE_1__* dstr; } ;
struct TYPE_2__ {int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  HIFN_DSTR_SYNC (struct hifn_softc*,int,int) ; 
 int HIFN_D_DST_RSIZE ; 
 int HIFN_D_JUMP ; 
 int HIFN_D_MASKDONEIRQ ; 
 int HIFN_D_VALID ; 
 int /*<<< orphan*/  htole32 (int) ; 

__attribute__((used)) static __inline int
hifn_dmamap_dstwrap(struct hifn_softc *sc, int idx)
{
	struct hifn_dma *dma = sc->sc_dma;

	if (++idx == HIFN_D_DST_RSIZE) {
		dma->dstr[idx].l = htole32(HIFN_D_VALID | HIFN_D_JUMP |
		    HIFN_D_MASKDONEIRQ);
		HIFN_DSTR_SYNC(sc, idx,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		idx = 0;
	}
	return (idx);
}