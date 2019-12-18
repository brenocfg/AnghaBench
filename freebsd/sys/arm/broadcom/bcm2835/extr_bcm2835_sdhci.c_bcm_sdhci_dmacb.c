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
struct bcm_sdhci_softc {int dmamap_status; int dmamap_seg_count; int /*<<< orphan*/ * dmamap_seg_sizes; int /*<<< orphan*/ * dmamap_seg_addrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
bcm_sdhci_dmacb(void *arg, bus_dma_segment_t *segs, int nseg, int err)
{
	struct bcm_sdhci_softc *sc = arg;
	int i;

	sc->dmamap_status = err;
	sc->dmamap_seg_count = nseg;

	/* Note nseg is guaranteed to be zero if err is non-zero. */
	for (i = 0; i < nseg; i++) {
		sc->dmamap_seg_addrs[i] = segs[i].ds_addr;
		sc->dmamap_seg_sizes[i] = segs[i].ds_len;
	}
}