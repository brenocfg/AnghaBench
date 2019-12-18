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
typedef  int uint32_t ;
struct sc_pcminfo {struct aic_softc* sc; } ;
struct sc_chinfo {int /*<<< orphan*/  buffer; struct sc_pcminfo* parent; } ;
struct aic_softc {int dma_size; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int sndbuf_getblksz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
aicchan_setblocksize(kobj_t obj, void *data, uint32_t blocksize)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct aic_softc *sc;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

	sndbuf_resize(ch->buffer, sc->dma_size / blocksize, blocksize);

	return (sndbuf_getblksz(ch->buffer));
}