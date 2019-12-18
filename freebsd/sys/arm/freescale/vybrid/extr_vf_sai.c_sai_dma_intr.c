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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcd_conf {int nbytes; int nmajor; } ;
struct sc_pcminfo {struct sc_info* sc; struct sc_chinfo* chan; } ;
struct sc_info {scalar_t__ pos; scalar_t__ dma_size; struct tcd_conf* tcd; } ;
struct sc_chinfo {int /*<<< orphan*/  channel; scalar_t__ run; } ;

/* Variables and functions */
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 

uint32_t
sai_dma_intr(void *arg, int chn)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	struct tcd_conf *tcd;

	scp = arg;
	ch = &scp->chan[0];

	sc = scp->sc;
	tcd = sc->tcd;

	sc->pos += (tcd->nbytes * tcd->nmajor);
	if (sc->pos >= sc->dma_size)
		sc->pos -= sc->dma_size;

	if (ch->run)
		chn_intr(ch->channel);

	return (0);
}