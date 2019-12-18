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
struct xdma_channel {int caps; void* chan; } ;
struct msgdma_softc {struct msgdma_channel* channels; } ;
struct msgdma_channel {int used; int index; int descs_num; scalar_t__ descs_used_count; scalar_t__ idx_tail; scalar_t__ idx_head; struct msgdma_softc* sc; struct xdma_channel* xchan; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MSGDMA_NCHANNELS ; 
 int XCHAN_CAP_BUSDMA ; 
 int XCHAN_CAP_IOMMU ; 
 struct msgdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msgdma_channel_alloc(device_t dev, struct xdma_channel *xchan)
{
	struct msgdma_channel *chan;
	struct msgdma_softc *sc;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < MSGDMA_NCHANNELS; i++) {
		chan = &sc->channels[i];
		if (chan->used == 0) {
			chan->xchan = xchan;
			xchan->chan = (void *)chan;
			if ((xchan->caps & XCHAN_CAP_IOMMU) == 0)
				xchan->caps |= XCHAN_CAP_BUSDMA;
			chan->index = i;
			chan->sc = sc;
			chan->used = 1;
			chan->idx_head = 0;
			chan->idx_tail = 0;
			chan->descs_used_count = 0;
			chan->descs_num = 1024;

			return (0);
		}
	}

	return (-1);
}