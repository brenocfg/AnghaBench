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
struct msgdma_softc {int dummy; } ;
struct msgdma_channel {scalar_t__ used; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct msgdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgdma_desc_free (struct msgdma_softc*,struct msgdma_channel*) ; 

__attribute__((used)) static int
msgdma_channel_free(device_t dev, struct xdma_channel *xchan)
{
	struct msgdma_channel *chan;
	struct msgdma_softc *sc;

	sc = device_get_softc(dev);

	chan = (struct msgdma_channel *)xchan->chan;

	msgdma_desc_free(sc, chan);

	chan->used = 0;

	return (0);
}