#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sc_pchinfo {int run; TYPE_1__* master; TYPE_1__* slave; struct sc_info* parent; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_4__ {int speed; scalar_t__ stereo; scalar_t__ b16; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  emu_enatimer (struct sc_info*,int) ; 
 int /*<<< orphan*/  emu_settimer (struct sc_info*) ; 
 int /*<<< orphan*/  emu_vdump (struct sc_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  emu_vsetup (struct sc_pchinfo*) ; 
 int /*<<< orphan*/  emu_vtrigger (struct sc_info*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  emu_vwrite (struct sc_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emupchan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_pchinfo *ch = data;
	struct sc_info *sc = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	snd_mtxlock(sc->lock);
	if (go == PCMTRIG_START) {
		emu_vsetup(ch);
		emu_vwrite(sc, ch->master);
		emu_settimer(sc);
		emu_enatimer(sc, 1);
#ifdef EMUDEBUG
		printf("start [%d bit, %s, %d hz]\n",
			ch->master->b16 ? 16 : 8,
			ch->master->stereo ? "stereo" : "mono",
			ch->master->speed);
		emu_vdump(sc, ch->master);
		emu_vdump(sc, ch->slave);
#endif
	}
	ch->run = (go == PCMTRIG_START) ? 1 : 0;
	emu_vtrigger(sc, ch->master, ch->run);
	snd_mtxunlock(sc->lock);
	return 0;
}