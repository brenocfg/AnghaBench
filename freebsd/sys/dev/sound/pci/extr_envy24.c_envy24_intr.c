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
typedef  int u_int32_t ;
struct sc_info {int psize; int* blk; int* intr; int rsize; int /*<<< orphan*/  lock; struct sc_chinfo* chan; int /*<<< orphan*/  dev; } ;
struct sc_chinfo {int blk; int /*<<< orphan*/  channel; scalar_t__ run; } ;

/* Variables and functions */
 int ENVY24_CHAN_PLAY_DAC1 ; 
 int ENVY24_CHAN_PLAY_SPDIF ; 
 int ENVY24_CHAN_REC_ADC1 ; 
 int ENVY24_CHAN_REC_SPDIF ; 
 int /*<<< orphan*/  ENVY24_MT_PCNT ; 
 int /*<<< orphan*/  ENVY24_MT_RCNT ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ envy24_checkintr (struct sc_info*,int /*<<< orphan*/ ) ; 
 int envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_updintr (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
envy24_intr(void *p)
{
	struct sc_info *sc = (struct sc_info *)p;
	struct sc_chinfo *ch;
	u_int32_t ptr, dsize, feed;
	int i;

#if(0)
	device_printf(sc->dev, "envy24_intr()\n");
#endif
	snd_mtxlock(sc->lock);
	if (envy24_checkintr(sc, PCMDIR_PLAY)) {
#if(0)
		device_printf(sc->dev, "envy24_intr(): play\n");
#endif
		dsize = sc->psize / 4;
		ptr = dsize - envy24_rdmt(sc, ENVY24_MT_PCNT, 2) - 1;
#if(0)
		device_printf(sc->dev, "envy24_intr(): ptr = %d-->", ptr);
#endif
		ptr -= ptr % sc->blk[0];
		feed = (ptr + dsize - sc->intr[0]) % dsize; 
#if(0)
		printf("%d intr = %d feed = %d\n", ptr, sc->intr[0], feed);
#endif
		for (i = ENVY24_CHAN_PLAY_DAC1; i <= ENVY24_CHAN_PLAY_SPDIF; i++) {
			ch = &sc->chan[i];
#if(0)
			if (ch->run)
				device_printf(sc->dev, "envy24_intr(): chan[%d].blk = %d\n", i, ch->blk);
#endif
			if (ch->run && ch->blk <= feed) {
				snd_mtxunlock(sc->lock);
				chn_intr(ch->channel);
				snd_mtxlock(sc->lock);
			}
		}
		sc->intr[0] = ptr;
		envy24_updintr(sc, PCMDIR_PLAY);
	}
	if (envy24_checkintr(sc, PCMDIR_REC)) {
#if(0)
		device_printf(sc->dev, "envy24_intr(): rec\n");
#endif
		dsize = sc->rsize / 4;
		ptr = dsize - envy24_rdmt(sc, ENVY24_MT_RCNT, 2) - 1;
		ptr -= ptr % sc->blk[1];
		feed = (ptr + dsize - sc->intr[1]) % dsize; 
		for (i = ENVY24_CHAN_REC_ADC1; i <= ENVY24_CHAN_REC_SPDIF; i++) {
			ch = &sc->chan[i];
			if (ch->run && ch->blk <= feed) {
				snd_mtxunlock(sc->lock);
				chn_intr(ch->channel);
				snd_mtxlock(sc->lock);
			}
		}
		sc->intr[1] = ptr;
		envy24_updintr(sc, PCMDIR_REC);
	}
	snd_mtxunlock(sc->lock);

	return;
}