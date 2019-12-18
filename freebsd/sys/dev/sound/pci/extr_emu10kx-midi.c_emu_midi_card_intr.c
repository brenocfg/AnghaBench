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
typedef  int /*<<< orphan*/  uint32_t ;
struct emu_midi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* mpu_intr ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  mpu; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_mread (void*,struct emu_midi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
emu_midi_card_intr(void *p, uint32_t intr_status)
{
	struct emu_midi_softc *sc = (struct emu_midi_softc *)p;
	if (sc->mpu_intr)
		(sc->mpu_intr) (sc->mpu);
	if (sc->mpu_intr == NULL) {
		/* We should read MIDI event to unlock card after
		 * interrupt. XXX - check, why this happens.  */
		if (bootverbose)
			device_printf(sc->dev, "midi interrupt %08x without interrupt handler, force mread!\n", intr_status);
		(void)emu_mread((void *)(NULL), sc, 0);
	}
	return (intr_status); /* Acknowledge everything */
}