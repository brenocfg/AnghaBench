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
struct sc_info {int hasvra; int hasvrm; struct sc_chinfo* ch; int /*<<< orphan*/  codec; } ;
struct sc_chinfo {int /*<<< orphan*/  spd; int /*<<< orphan*/  blksz; scalar_t__ run_save; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ICH_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  ICH_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  PCMTRIG_START ; 
 int /*<<< orphan*/  ac97_setextmode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ich_init (struct sc_info*) ; 
 int /*<<< orphan*/  ich_pci_codec_reset (struct sc_info*) ; 
 int /*<<< orphan*/  ichchan_setblocksize (int /*<<< orphan*/ ,struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichchan_setspeed (int /*<<< orphan*/ ,struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichchan_trigger (int /*<<< orphan*/ ,struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ich_pci_resume(device_t dev)
{
	struct sc_info *sc;
	int i;

	sc = pcm_getdevinfo(dev);

	ICH_LOCK(sc);
	/* Reinit audio device */
    	if (ich_init(sc) == -1) {
		device_printf(dev, "unable to reinitialize the card\n");
		ICH_UNLOCK(sc);
		return (ENXIO);
	}
	/* Reinit mixer */
	ich_pci_codec_reset(sc);
	ICH_UNLOCK(sc);
	ac97_setextmode(sc->codec, sc->hasvra | sc->hasvrm);
    	if (mixer_reinit(dev) == -1) {
		device_printf(dev, "unable to reinitialize the mixer\n");
		return (ENXIO);
	}
	/* Re-start DMA engines */
	for (i = 0 ; i < 3; i++) {
		struct sc_chinfo *ch = &sc->ch[i];
		if (sc->ch[i].run_save) {
			ichchan_setblocksize(0, ch, ch->blksz);
			ichchan_setspeed(0, ch, ch->spd);
			ichchan_trigger(0, ch, PCMTRIG_START);
		}
	}
	return (0);
}