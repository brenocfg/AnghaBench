#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  spd; scalar_t__ dma_was_active; } ;
struct sc_info {int /*<<< orphan*/  lock; TYPE_1__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  cmi_ch0_start (struct sc_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  cmi_ch1_start (struct sc_info*,TYPE_1__*) ; 
 scalar_t__ cmi_init (struct sc_info*) ; 
 int /*<<< orphan*/  cmi_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmichan_setformat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmichan_setspeed (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmi_resume(device_t dev)
{
	struct sc_info *sc = pcm_getdevinfo(dev);

	snd_mtxlock(sc->lock);
	cmi_power(sc, 0);
	if (cmi_init(sc) != 0) {
		device_printf(dev, "unable to reinitialize the card\n");
		snd_mtxunlock(sc->lock);
		return ENXIO;
	}

	if (mixer_reinit(dev) == -1) {
		device_printf(dev, "unable to reinitialize the mixer\n");
		snd_mtxunlock(sc->lock);
                return ENXIO;
        }

	if (sc->pch.dma_was_active) {
		cmichan_setspeed(NULL, &sc->pch, sc->pch.spd);
		cmichan_setformat(NULL, &sc->pch, sc->pch.fmt);
		cmi_ch0_start(sc, &sc->pch);
	}

	if (sc->rch.dma_was_active) {
		cmichan_setspeed(NULL, &sc->rch, sc->rch.spd);
		cmichan_setformat(NULL, &sc->rch, sc->rch.fmt);
		cmi_ch1_start(sc, &sc->rch);
	}
	snd_mtxunlock(sc->lock);
	return 0;
}