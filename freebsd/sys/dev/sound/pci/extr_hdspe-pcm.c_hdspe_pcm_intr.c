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
struct sc_pcminfo {int chnum; struct sc_chinfo* chan; struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
hdspe_pcm_intr(struct sc_pcminfo *scp)
{
	struct sc_chinfo *ch;
	struct sc_info *sc;
	int i;

	sc = scp->sc;

	for (i = 0; i < scp->chnum; i++) {
		ch = &scp->chan[i];
		snd_mtxunlock(sc->lock);
		chn_intr(ch->channel);
		snd_mtxlock(sc->lock);
	}

	return (0);
}