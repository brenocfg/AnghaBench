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
struct xdma_channel {int /*<<< orphan*/  caps; void* chan; } ;
struct pl330_softc {struct pl330_channel* channels; } ;
struct pl330_channel {int used; int index; void* ibuf; int /*<<< orphan*/  ibuf_phys; struct pl330_softc* sc; struct xdma_channel* xchan; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ZERO ; 
 int PAGE_SIZE ; 
 int PL330_NCHANNELS ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  XCHAN_CAP_BUSDMA ; 
 struct pl330_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ kmem_alloc_contig (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (void*) ; 

__attribute__((used)) static int
pl330_channel_alloc(device_t dev, struct xdma_channel *xchan)
{
	struct pl330_channel *chan;
	struct pl330_softc *sc;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < PL330_NCHANNELS; i++) {
		chan = &sc->channels[i];
		if (chan->used == 0) {
			chan->xchan = xchan;
			xchan->chan = (void *)chan;
			xchan->caps |= XCHAN_CAP_BUSDMA;
			chan->index = i;
			chan->sc = sc;
			chan->used = 1;

			chan->ibuf = (void *)kmem_alloc_contig(PAGE_SIZE * 8,
			    M_ZERO, 0, ~0, PAGE_SIZE, 0,
			    VM_MEMATTR_UNCACHEABLE);
			chan->ibuf_phys = vtophys(chan->ibuf);

			return (0);
		}
	}

	return (-1);
}