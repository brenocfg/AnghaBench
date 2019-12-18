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
struct sc_pcminfo {int /*<<< orphan*/  dev; struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {int /*<<< orphan*/  run; struct sc_pcminfo* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 132 
#define  PCMTRIG_EMLDMARD 131 
#define  PCMTRIG_EMLDMAWR 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  buffer_copy (struct sc_chinfo*) ; 
 int /*<<< orphan*/  clean (struct sc_chinfo*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdspe_start_audio (struct sc_info*) ; 
 int /*<<< orphan*/  hdspe_stop_audio (struct sc_info*) ; 
 int /*<<< orphan*/  hdspechan_enable (struct sc_chinfo*,int) ; 
 int /*<<< orphan*/  hdspechan_setgain (struct sc_chinfo*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdspechan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

	snd_mtxlock(sc->lock);
	switch (go) {
	case PCMTRIG_START:
#if 0
		device_printf(scp->dev, "hdspechan_trigger(): start\n");
#endif
		hdspechan_enable(ch, 1);
		hdspechan_setgain(ch);
		hdspe_start_audio(sc);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
#if 0
		device_printf(scp->dev, "hdspechan_trigger(): stop or abort\n");
#endif
		clean(ch);
		hdspechan_enable(ch, 0);
		hdspe_stop_audio(sc);
		break;

	case PCMTRIG_EMLDMAWR:
	case PCMTRIG_EMLDMARD:
		if(ch->run)
			buffer_copy(ch);
		break;
	}

	snd_mtxunlock(sc->lock);

	return (0);
}