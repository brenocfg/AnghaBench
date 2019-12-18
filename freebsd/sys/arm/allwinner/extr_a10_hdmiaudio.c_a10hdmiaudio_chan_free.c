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
struct a10hdmiaudio_info {int /*<<< orphan*/  dmat; } ;
struct a10hdmiaudio_chinfo {int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmaaddr; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; struct a10hdmiaudio_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_DMA_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10hdmiaudio_chan_free(kobj_t obj, void *data)
{
	struct a10hdmiaudio_chinfo *ch = data;
	struct a10hdmiaudio_info *sc = ch->parent;

	SUNXI_DMA_FREE(ch->dmac, ch->dmachan);
	bus_dmamap_unload(sc->dmat, ch->dmamap);
	bus_dmamem_free(sc->dmat, ch->dmaaddr, ch->dmamap);

	return (0);
}