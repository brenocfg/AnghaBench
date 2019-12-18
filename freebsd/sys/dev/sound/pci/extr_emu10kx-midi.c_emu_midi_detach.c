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
struct emu_midi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  ihandle; int /*<<< orphan*/  card; int /*<<< orphan*/  mpu; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct emu_midi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_intr_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpu401_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emu_midi_detach(device_t dev)
{
	struct emu_midi_softc *scp;

	scp = device_get_softc(dev);
	mpu401_uninit(scp->mpu);
	emu_intr_unregister(scp->card, scp->ihandle);
	mtx_destroy(&scp->mtx);
	return (0);
}