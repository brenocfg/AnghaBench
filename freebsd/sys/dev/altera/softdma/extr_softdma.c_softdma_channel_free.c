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
struct xdma_channel {scalar_t__ chan; } ;
struct softdma_softc {int dummy; } ;
struct softdma_channel {scalar_t__ used; int /*<<< orphan*/ * descs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct softdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
softdma_channel_free(device_t dev, struct xdma_channel *xchan)
{
	struct softdma_channel *chan;
	struct softdma_softc *sc;

	sc = device_get_softc(dev);

	chan = (struct softdma_channel *)xchan->chan;

	if (chan->descs != NULL) {
		free(chan->descs, M_DEVBUF);
	}

	chan->used = 0;

	return (0);
}