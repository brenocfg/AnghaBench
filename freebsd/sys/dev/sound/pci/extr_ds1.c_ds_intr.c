#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct sc_info {int currbank; int /*<<< orphan*/  lock; TYPE_2__* rch; TYPE_1__* pch; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; scalar_t__ run; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; scalar_t__ run; } ;

/* Variables and functions */
 int DS1_CHANS ; 
 int /*<<< orphan*/  YDSXGR_CTRLSELECT ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  YDSXGR_STATUS ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ds_intr(void *p)
{
	struct sc_info *sc = (struct sc_info *)p;
	u_int32_t i, x;

	snd_mtxlock(sc->lock);
	i = ds_rd(sc, YDSXGR_STATUS, 4);
	if (i & 0x00008000)
		device_printf(sc->dev, "timeout irq\n");
	if (i & 0x80008000) {
		ds_wr(sc, YDSXGR_STATUS, i & 0x80008000, 4);
		sc->currbank = ds_rd(sc, YDSXGR_CTRLSELECT, 4) & 0x00000001;

		x = 0;
		for (i = 0; i < DS1_CHANS; i++) {
			if (sc->pch[i].run) {
				x = 1;
				snd_mtxunlock(sc->lock);
				chn_intr(sc->pch[i].channel);
				snd_mtxlock(sc->lock);
			}
		}
		for (i = 0; i < 2; i++) {
			if (sc->rch[i].run) {
				x = 1;
				snd_mtxunlock(sc->lock);
				chn_intr(sc->rch[i].channel);
				snd_mtxlock(sc->lock);
			}
		}
		i = ds_rd(sc, YDSXGR_MODE, 4);
		if (x)
			ds_wr(sc, YDSXGR_MODE, i | 0x00000002, 4);

	}
	snd_mtxunlock(sc->lock);
}