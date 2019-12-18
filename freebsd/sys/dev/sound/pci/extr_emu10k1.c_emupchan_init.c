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
struct snd_dbuf {int dummy; } ;
struct sc_pchinfo {int blksz; int spd; struct snd_dbuf* buffer; void* slave; void* master; int /*<<< orphan*/  fmt; struct pcm_channel* channel; struct sc_info* parent; } ;
struct sc_info {int bufsz; int /*<<< orphan*/  lock; int /*<<< orphan*/  pnum; struct sc_pchinfo* pch; } ;
struct pcm_channel {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_U8 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  SND_FORMAT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* emu_valloc (struct sc_info*) ; 
 scalar_t__ emu_vinit (struct sc_info*,void*,void*,int,struct snd_dbuf*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
emupchan_init(kobj_t obj, void *devinfo, struct snd_dbuf *b,
    struct pcm_channel *c, int dir)
{
	struct sc_info *sc = devinfo;
	struct sc_pchinfo *ch;
	void *r;

	KASSERT(dir == PCMDIR_PLAY, ("emupchan_init: bad direction"));
	ch = &sc->pch[sc->pnum++];
	ch->buffer = b;
	ch->parent = sc;
	ch->channel = c;
	ch->blksz = sc->bufsz / 2;
	ch->fmt = SND_FORMAT(AFMT_U8, 1, 0);
	ch->spd = 8000;
	snd_mtxlock(sc->lock);
	ch->master = emu_valloc(sc);
	ch->slave = emu_valloc(sc);
	snd_mtxunlock(sc->lock);
	r = (emu_vinit(sc, ch->master, ch->slave, sc->bufsz, ch->buffer))
	    ? NULL : ch;

	return r;
}