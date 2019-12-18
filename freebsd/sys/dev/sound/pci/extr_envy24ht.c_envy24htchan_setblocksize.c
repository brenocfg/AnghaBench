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
typedef  int u_int32_t ;
struct sc_chinfo {int size; int blk; int unit; scalar_t__ dir; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENVY24HT_PLAY_BUFUNIT ; 
 int ENVY24HT_REC_BUFUNIT ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static u_int32_t
envy24htchan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct sc_chinfo *ch = data;
	/* struct sc_info *sc = ch->parent; */
	u_int32_t size, prev;
	unsigned int bcnt, bsize;

#if(0)
	device_printf(sc->dev, "envy24htchan_setblocksize(obj, data, %d)\n", blocksize);
#endif
	prev = 0x7fffffff;
	/* snd_mtxlock(sc->lock); */
	for (size = ch->size / 2; size > 0; size /= 2) {
		if (abs(size - blocksize) < abs(prev - blocksize))
			prev = size;
		else
			break;
	}

	ch->blk = prev / ch->unit;
	if (ch->dir == PCMDIR_PLAY)
		ch->blk *= ENVY24HT_PLAY_BUFUNIT / 4;
	else
		ch->blk *= ENVY24HT_REC_BUFUNIT / 4;
        /* set channel buffer information */
        /* ch->size = ch->unit * ENVY24HT_SAMPLE_NUM; */
        if (ch->dir == PCMDIR_PLAY)
                bsize = ch->blk * 4 / ENVY24HT_PLAY_BUFUNIT;
        else
                bsize = ch->blk * 4 / ENVY24HT_REC_BUFUNIT;
        bsize *= ch->unit;
        bcnt = ch->size / bsize;
        sndbuf_resize(ch->buffer, bcnt, bsize);
	/* snd_mtxunlock(sc->lock); */

#if(0)
	device_printf(sc->dev, "envy24htchan_setblocksize(): return %d\n", prev);
#endif
	return prev;
}