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
struct sc_info {int /*<<< orphan*/  lock; TYPE_2__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  als_capture_start (TYPE_2__*) ; 
 scalar_t__ als_init (struct sc_info*) ; 
 int /*<<< orphan*/  als_playback_start (TYPE_1__*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
als_pci_resume(device_t dev)
{
	struct sc_info *sc = pcm_getdevinfo(dev);


	snd_mtxlock(sc->lock);
	if (als_init(sc) != 0) {
		device_printf(dev, "unable to reinitialize the card\n");
		snd_mtxunlock(sc->lock);
		return ENXIO;
	}

	if (mixer_reinit(dev) != 0) {
		device_printf(dev, "unable to reinitialize the mixer\n");
		snd_mtxunlock(sc->lock);
		return ENXIO;
	}

	if (sc->pch.dma_was_active) {
		als_playback_start(&sc->pch);
	}

	if (sc->rch.dma_was_active) {
		als_capture_start(&sc->rch);
	}
	snd_mtxunlock(sc->lock);

	return 0;
}