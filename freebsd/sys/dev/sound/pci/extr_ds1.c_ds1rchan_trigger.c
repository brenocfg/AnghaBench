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
struct sc_rchinfo {int run; scalar_t__ num; struct sc_info* parent; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ DS1_RECPRIMARY ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  YDSXGR_MAPOFREC ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int ds_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds_setuprch (struct sc_rchinfo*) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1rchan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_rchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	u_int32_t x;

	if (!PCMTRIG_COMMON(go))
		return 0;
	if (go == PCMTRIG_START) {
		ch->run = 1;
		ds_setuprch(ch);
		snd_mtxlock(sc->lock);
		x = ds_rd(sc, YDSXGR_MAPOFREC, 4);
		x |= (ch->num == DS1_RECPRIMARY)? 0x02 : 0x01;
		ds_wr(sc, YDSXGR_MAPOFREC, x, 4);
		ds_wr(sc, YDSXGR_MODE, 0x00000003, 4);
		snd_mtxunlock(sc->lock);
	} else {
		ch->run = 0;
		snd_mtxlock(sc->lock);
		x = ds_rd(sc, YDSXGR_MAPOFREC, 4);
		x &= ~((ch->num == DS1_RECPRIMARY)? 0x02 : 0x01);
		ds_wr(sc, YDSXGR_MAPOFREC, x, 4);
		snd_mtxunlock(sc->lock);
	}

	return 0;
}