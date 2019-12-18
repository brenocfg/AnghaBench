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
struct a31dmac_softc {int dummy; } ;
struct a31dmac_channel {int /*<<< orphan*/  index; struct a31dmac_softc* sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_EN_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WRITE (struct a31dmac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a31dmac_halt(device_t dev, void *priv)
{
	struct a31dmac_channel *ch;
	struct a31dmac_softc *sc;

	ch = priv;
	sc = ch->sc;

	DMA_WRITE(sc, DMA_EN_REG(ch->index), 0);
}