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
struct aw_mmc_softc {int aw_dma_map_err; int /*<<< orphan*/  aw_dma_desc_phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
aw_dma_desc_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int err)
{
	struct aw_mmc_softc *sc;

	sc = (struct aw_mmc_softc *)arg;
	if (err) {
		sc->aw_dma_map_err = err;
		return;
	}
	sc->aw_dma_desc_phys = segs[0].ds_addr;
}