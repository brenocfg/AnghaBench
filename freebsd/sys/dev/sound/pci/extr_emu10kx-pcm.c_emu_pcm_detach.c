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
struct emu_pcm_info {scalar_t__ lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  emu_pcm_uninit (struct emu_pcm_info*) ; 
 int /*<<< orphan*/  free (struct emu_pcm_info*,int /*<<< orphan*/ ) ; 
 struct emu_pcm_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 

__attribute__((used)) static int
emu_pcm_detach(device_t dev)
{
	int r;
	struct emu_pcm_info *sc;

	sc = pcm_getdevinfo(dev);

	r = pcm_unregister(dev);

	if (r) 	return (r);

	emu_pcm_uninit(sc);

	if (sc->lock)
		snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);

	return (0);
}