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
struct sc_pchinfo {int run; int /*<<< orphan*/  rsnum; int /*<<< orphan*/  lsnum; int /*<<< orphan*/  fmt; struct sc_info* parent; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  ds_enapslot (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds_setuppch (struct sc_pchinfo*) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1pchan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_pchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	int stereo;

	if (!PCMTRIG_COMMON(go))
		return 0;
	stereo = (AFMT_CHANNEL(ch->fmt) > 1)? 1 : 0;
	if (go == PCMTRIG_START) {
		ch->run = 1;
		ds_setuppch(ch);
		ds_enapslot(sc, ch->lsnum, 1);
		ds_enapslot(sc, ch->rsnum, stereo);
		snd_mtxlock(sc->lock);
		ds_wr(sc, YDSXGR_MODE, 0x00000003, 4);
		snd_mtxunlock(sc->lock);
	} else {
		ch->run = 0;
		/* ds_setuppch(ch); */
		ds_enapslot(sc, ch->lsnum, 0);
		ds_enapslot(sc, ch->rsnum, 0);
	}

	return 0;
}