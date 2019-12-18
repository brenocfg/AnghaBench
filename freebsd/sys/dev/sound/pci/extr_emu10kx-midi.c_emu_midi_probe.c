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
struct emu_midi_softc {int is_emu10k1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 uintptr_t BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int /*<<< orphan*/  EMU_VAR_ISEMU10K1 ; 
 int ENXIO ; 
 uintptr_t SCF_MIDI ; 
 int /*<<< orphan*/  bzero (struct emu_midi_softc*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct emu_midi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
emu_midi_probe(device_t dev)
{
	struct emu_midi_softc *scp;
	uintptr_t func, r, is_emu10k1;

	r = BUS_READ_IVAR(device_get_parent(dev), dev, 0, &func);
	if (func != SCF_MIDI)
		return (ENXIO);

	scp = device_get_softc(dev);
	bzero(scp, sizeof(*scp));
	r = BUS_READ_IVAR(device_get_parent(dev), dev, EMU_VAR_ISEMU10K1, &is_emu10k1);
	scp->is_emu10k1 = is_emu10k1 ? 1 : 0;

	device_set_desc(dev, "EMU10Kx MIDI Interface");
	return (0);
}