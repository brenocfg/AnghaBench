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
struct dwmmc_softc {TYPE_1__* desc_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {int des0; int /*<<< orphan*/  des2; int /*<<< orphan*/  des1; } ;

/* Variables and functions */
 int DES0_CH ; 
 int DES0_DIC ; 
 int DES0_FS ; 
 int DES0_LD ; 
 int DES0_OWN ; 
 int /*<<< orphan*/  dprintf (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwmmc_ring_setup(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct dwmmc_softc *sc;
	int idx;

	if (error != 0)
		return;

	sc = arg;

	dprintf("nsegs %d seg0len %lu\n", nsegs, segs[0].ds_len);

	for (idx = 0; idx < nsegs; idx++) {
		sc->desc_ring[idx].des0 = (DES0_OWN | DES0_DIC | DES0_CH);
		sc->desc_ring[idx].des1 = segs[idx].ds_len;
		sc->desc_ring[idx].des2 = segs[idx].ds_addr;

		if (idx == 0)
			sc->desc_ring[idx].des0 |= DES0_FS;

		if (idx == (nsegs - 1)) {
			sc->desc_ring[idx].des0 &= ~(DES0_DIC | DES0_CH);
			sc->desc_ring[idx].des0 |= DES0_LD;
		}
	}
}