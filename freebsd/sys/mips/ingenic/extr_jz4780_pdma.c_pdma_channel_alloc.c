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
struct xdma_channel {void* chan; } ;
struct pdma_softc {int dummy; } ;
struct pdma_channel {int used; int index; struct xdma_channel* xchan; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PDMA_NCHANNELS ; 
 struct pdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdma_channel_setup_descriptors (int /*<<< orphan*/ ,struct pdma_channel*) ; 
 struct pdma_channel* pdma_channels ; 

__attribute__((used)) static int
pdma_channel_alloc(device_t dev, struct xdma_channel *xchan)
{
	struct pdma_channel *chan;
	struct pdma_softc *sc;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < PDMA_NCHANNELS; i++) {
		chan = &pdma_channels[i];
		if (chan->used == 0) {
			chan->xchan = xchan;
			xchan->chan = (void *)chan;
			chan->used = 1;
			chan->index = i;

			pdma_channel_setup_descriptors(dev, chan);

			return (0);
		}
	}

	return (-1);
}