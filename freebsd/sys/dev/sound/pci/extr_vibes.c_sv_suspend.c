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
struct TYPE_2__ {int /*<<< orphan*/  dma_active; int /*<<< orphan*/  dma_was_active; } ;
struct sc_info {TYPE_1__ pch; TYPE_1__ rch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_ABORT ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_mix_mute_all (struct sc_info*) ; 
 int /*<<< orphan*/  sv_power (struct sc_info*,int) ; 
 int /*<<< orphan*/  svrchan_trigger (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sv_suspend(device_t dev)
{
	struct sc_info	*sc = pcm_getdevinfo(dev);

	sc->rch.dma_was_active = sc->rch.dma_active;
	svrchan_trigger(NULL, &sc->rch, PCMTRIG_ABORT);

	sc->pch.dma_was_active = sc->pch.dma_active;
	svrchan_trigger(NULL, &sc->pch, PCMTRIG_ABORT);

	sv_mix_mute_all(sc);
	sv_power(sc, 3);

	return 0;
}