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
struct TYPE_4__ {int /*<<< orphan*/  dma_was_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_was_active; } ;
struct sc_info {int /*<<< orphan*/  lock; TYPE_2__ rch; TYPE_1__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  als_capture_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  als_playback_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  als_uninit (struct sc_info*) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
als_pci_suspend(device_t dev)
{
	struct sc_info *sc = pcm_getdevinfo(dev);

	snd_mtxlock(sc->lock);
	sc->pch.dma_was_active = als_playback_stop(&sc->pch);
	sc->rch.dma_was_active = als_capture_stop(&sc->rch);
	als_uninit(sc);
	snd_mtxunlock(sc->lock);
	return 0;
}