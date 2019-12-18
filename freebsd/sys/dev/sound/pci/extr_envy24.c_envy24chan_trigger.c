#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct sc_info {int* run; int* blk; int /*<<< orphan*/  lock; TYPE_3__* chan; int /*<<< orphan*/ * intr; int /*<<< orphan*/  dev; int /*<<< orphan*/  speed; TYPE_1__* caps; } ;
struct sc_chinfo {scalar_t__ dir; int offset; int blk; int size; int unit; int run; int /*<<< orphan*/  num; int /*<<< orphan*/  (* emldma ) (struct sc_chinfo*) ;TYPE_2__* channel; int /*<<< orphan*/  speed; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_6__ {scalar_t__ dir; int run; int blk; } ;
struct TYPE_5__ {int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  maxspeed; int /*<<< orphan*/  minspeed; } ;

/* Variables and functions */
 int ENVY24_CHAN_NUM ; 
 int ENVY24_SAMPLE_NUM ; 
 scalar_t__ PCMDIR_PLAY ; 
#define  PCMTRIG_ABORT 131 
#define  PCMTRIG_EMLDMARD 130 
#define  PCMTRIG_EMLDMAWR 129 
#define  PCMTRIG_START 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int envy24_gethwptr (struct sc_info*,scalar_t__) ; 
 int /*<<< orphan*/  envy24_mutevolume (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_setspeed (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_setvolume (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  envy24_start (struct sc_info*,scalar_t__) ; 
 int /*<<< orphan*/  envy24_stop (struct sc_info*,scalar_t__) ; 
 int /*<<< orphan*/  envy24_updintr (struct sc_info*,scalar_t__) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sc_chinfo*) ; 
 int /*<<< orphan*/  stub2 (struct sc_chinfo*) ; 
 int /*<<< orphan*/  stub3 (struct sc_chinfo*) ; 

__attribute__((used)) static int
envy24chan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;
	u_int32_t ptr;
	int slot;
	int error = 0;
#if 0
	int i;

	device_printf(sc->dev, "envy24chan_trigger(obj, data, %d)\n", go);
#endif
	snd_mtxlock(sc->lock);
	if (ch->dir == PCMDIR_PLAY)
		slot = 0;
	else
		slot = 1;
	switch (go) {
	case PCMTRIG_START:
#if(0)
		device_printf(sc->dev, "envy24chan_trigger(): start\n");
#endif
		/* check or set channel speed */
		if (sc->run[0] == 0 && sc->run[1] == 0) {
			sc->speed = envy24_setspeed(sc, ch->speed);
			sc->caps[0].minspeed = sc->caps[0].maxspeed = sc->speed;
			sc->caps[1].minspeed = sc->caps[1].maxspeed = sc->speed;
		}
		else if (ch->speed != 0 && ch->speed != sc->speed) {
			error = -1;
			goto fail;
		}
		if (ch->speed == 0)
			ch->channel->speed = sc->speed;
		/* start or enable channel */
		sc->run[slot]++;
		if (sc->run[slot] == 1) {
			/* first channel */
			ch->offset = 0;
			sc->blk[slot] = ch->blk;
		}
		else {
			ptr = envy24_gethwptr(sc, ch->dir);
			ch->offset = ((ptr / ch->blk + 1) * ch->blk %
			    (ch->size / 4)) * 4 / ch->unit;
			if (ch->blk < sc->blk[slot])
				sc->blk[slot] = ch->blk;
		}
		if (ch->dir == PCMDIR_PLAY) {
			ch->emldma(ch);
			envy24_setvolume(sc, ch->num);
		}
		envy24_updintr(sc, ch->dir);
		if (sc->run[slot] == 1)
			envy24_start(sc, ch->dir);
		ch->run = 1;
		break;
	case PCMTRIG_EMLDMAWR:
#if(0)
		device_printf(sc->dev, "envy24chan_trigger(): emldmawr\n");
#endif
		if (ch->run != 1) {
			error = -1;
			goto fail;
		}
		ch->emldma(ch);
		break;
	case PCMTRIG_EMLDMARD:
#if(0)
		device_printf(sc->dev, "envy24chan_trigger(): emldmard\n");
#endif
		if (ch->run != 1) {
			error = -1;
			goto fail;
		}
		ch->emldma(ch);
		break;
	case PCMTRIG_ABORT:
		if (ch->run) {
#if(0)
		device_printf(sc->dev, "envy24chan_trigger(): abort\n");
#endif
		ch->run = 0;
		sc->run[slot]--;
		if (ch->dir == PCMDIR_PLAY)
			envy24_mutevolume(sc, ch->num);
		if (sc->run[slot] == 0) {
			envy24_stop(sc, ch->dir);
			sc->intr[slot] = 0;
		}
#if 0
		else if (ch->blk == sc->blk[slot]) {
			sc->blk[slot] = ENVY24_SAMPLE_NUM / 2;
			for (i = 0; i < ENVY24_CHAN_NUM; i++) {
				if (sc->chan[i].dir == ch->dir &&
				    sc->chan[i].run == 1 &&
				    sc->chan[i].blk < sc->blk[slot])
					sc->blk[slot] = sc->chan[i].blk;
			}
			if (ch->blk != sc->blk[slot])
				envy24_updintr(sc, ch->dir);
		}
#endif
		}
		break;
	}
fail:
	snd_mtxunlock(sc->lock);
	return (error);
}