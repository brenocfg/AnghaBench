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
struct sc_pcminfo {struct aic_softc* sc; } ;
struct sc_chinfo {int run; struct sc_pcminfo* parent; } ;
struct aic_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  buf_base; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  aic_start (struct sc_pcminfo*) ; 
 int /*<<< orphan*/  aic_stop (struct sc_pcminfo*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aicchan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct aic_softc *sc;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

	snd_mtxlock(sc->lock);

	switch (go) {
	case PCMTRIG_START:
		ch->run = 1;

		sc->pos = 0;

		aic_start(scp);

		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		ch->run = 0;

		aic_stop(scp);

		sc->pos = 0;

		bzero(sc->buf_base, sc->dma_size);

		break;
	}

	snd_mtxunlock(sc->lock);

	return (0);
}