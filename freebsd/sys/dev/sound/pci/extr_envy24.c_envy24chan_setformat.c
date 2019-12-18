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
typedef  scalar_t__ u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct sc_chinfo {scalar_t__ dir; scalar_t__ format; int unit; int blk; int size; int /*<<< orphan*/  buffer; int /*<<< orphan*/  emldma; struct sc_info* parent; } ;
struct envy24_emldma {scalar_t__ format; int unit; int /*<<< orphan*/  emldma; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int ENVY24_PLAY_BUFUNIT ; 
 int ENVY24_REC_BUFUNIT ; 
 int ENVY24_SAMPLE_NUM ; 
 scalar_t__ PCMDIR_PLAY ; 
 int bcnt ; 
 int bsize ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct envy24_emldma* envy24_pemltab ; 
 struct envy24_emldma* envy24_remltab ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
envy24chan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;
	struct envy24_emldma *emltab;
	/* unsigned int bcnt, bsize; */
	int i;

#if(0)
	device_printf(sc->dev, "envy24chan_setformat(obj, data, 0x%08x)\n", format);
#endif
	snd_mtxlock(sc->lock);
	/* check and get format related information */
	if (ch->dir == PCMDIR_PLAY)
		emltab = envy24_pemltab;
	else
		emltab = envy24_remltab;
	if (emltab == NULL) {
		snd_mtxunlock(sc->lock);
		return -1;
	}
	for (i = 0; emltab[i].format != 0; i++)
		if (emltab[i].format == format)
			break;
	if (emltab[i].format == 0) {
		snd_mtxunlock(sc->lock);
		return -1;
	}

	/* set format information */
	ch->format = format;
	ch->emldma = emltab[i].emldma;
	if (ch->unit > emltab[i].unit)
		ch->blk *= ch->unit / emltab[i].unit;
	else
		ch->blk /= emltab[i].unit / ch->unit;
	ch->unit = emltab[i].unit;

	/* set channel buffer information */
	ch->size = ch->unit * ENVY24_SAMPLE_NUM;
#if 0
	if (ch->dir == PCMDIR_PLAY)
		bsize = ch->blk * 4 / ENVY24_PLAY_BUFUNIT;
	else
		bsize = ch->blk * 4 / ENVY24_REC_BUFUNIT;
	bsize *= ch->unit;
	bcnt = ch->size / bsize;
	sndbuf_resize(ch->buffer, bcnt, bsize);
#endif
	snd_mtxunlock(sc->lock);

#if(0)
	device_printf(sc->dev, "envy24chan_setformat(): return 0x%08x\n", 0);
#endif
	return 0;
}