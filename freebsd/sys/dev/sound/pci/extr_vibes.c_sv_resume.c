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
struct TYPE_4__ {scalar_t__ dma_was_active; } ;
struct TYPE_3__ {scalar_t__ dma_was_active; } ;
struct sc_info {TYPE_2__ pch; TYPE_1__ rch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCMTRIG_START ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int sv_init (struct sc_info*) ; 
 int /*<<< orphan*/  sv_mix_mute_all (struct sc_info*) ; 
 int /*<<< orphan*/  sv_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svpchan_trigger (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svrchan_trigger (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sv_resume(device_t dev)
{
	struct sc_info	*sc = pcm_getdevinfo(dev);

	sv_mix_mute_all(sc);
	sv_power(sc, 0);
	if (sv_init(sc) == -1) {
		device_printf(dev, "unable to reinitialize the card\n");
		return ENXIO;
	}

	if (mixer_reinit(dev) == -1) {
		device_printf(dev, "unable to reinitialize the mixer\n");
                return ENXIO;
        }

	if (sc->rch.dma_was_active) {
		svrchan_trigger(0, &sc->rch, PCMTRIG_START);
	}

	if (sc->pch.dma_was_active) {
		svpchan_trigger(0, &sc->pch, PCMTRIG_START);
	}

	return 0;
}