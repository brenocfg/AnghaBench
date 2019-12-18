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
struct TYPE_4__ {scalar_t__ active; } ;
struct TYPE_3__ {scalar_t__ active; } ;
struct sc_info {TYPE_2__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NM_AUDIO_MUTE_BOTH ; 
 int /*<<< orphan*/  NM_AUDIO_MUTE_REG ; 
 int /*<<< orphan*/  NM_PLAYBACK_ENABLE_REG ; 
 int /*<<< orphan*/  NM_RECORD_ENABLE_REG ; 
 int /*<<< orphan*/  nm_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nm_pci_suspend(device_t dev)
{
	struct sc_info *sc;

	sc = pcm_getdevinfo(dev);

	/* stop playing */
	if (sc->pch.active) {
		nm_wr(sc, NM_PLAYBACK_ENABLE_REG, 0, 1);
		nm_wr(sc, NM_AUDIO_MUTE_REG, NM_AUDIO_MUTE_BOTH, 2);
	}
	/* stop recording */
	if (sc->rch.active) {
		nm_wr(sc, NM_RECORD_ENABLE_REG, 0, 1);
	}
	return 0;
}