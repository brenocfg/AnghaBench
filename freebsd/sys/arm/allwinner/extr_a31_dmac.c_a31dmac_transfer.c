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
typedef  size_t uint32_t ;
struct a31dmac_softc {int dummy; } ;
struct a31dmac_channel {int /*<<< orphan*/  index; scalar_t__ physaddr; TYPE_1__* desc; struct a31dmac_softc* sc; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_2__ {void* next; void* bcnt; void* dstaddr; void* srcaddr; } ;

/* Variables and functions */
 size_t DMA_EN ; 
 int /*<<< orphan*/  DMA_EN_REG (int /*<<< orphan*/ ) ; 
 size_t DMA_NULL ; 
 int /*<<< orphan*/  DMA_STAR_ADDR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WRITE (struct a31dmac_softc*,int /*<<< orphan*/ ,size_t) ; 
 void* htole32 (size_t) ; 

__attribute__((used)) static int
a31dmac_transfer(device_t dev, void *priv, bus_addr_t src, bus_addr_t dst,
    size_t nbytes)
{
	struct a31dmac_channel *ch;
	struct a31dmac_softc *sc;

	ch = priv;
	sc = ch->sc;

	ch->desc->srcaddr = htole32((uint32_t)src);
	ch->desc->dstaddr = htole32((uint32_t)dst);
	ch->desc->bcnt = htole32(nbytes);
	ch->desc->next = htole32(DMA_NULL);

	DMA_WRITE(sc, DMA_STAR_ADDR_REG(ch->index), (uint32_t)ch->physaddr);
	DMA_WRITE(sc, DMA_EN_REG(ch->index), DMA_EN);

	return (0);
}