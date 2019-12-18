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
typedef  scalar_t__ vm_offset_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct cpcht_softc {int sc_populated_slots; scalar_t__ sc_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int in16rb (scalar_t__) ; 
 int in32rb (scalar_t__) ; 
 int in8rb (scalar_t__) ; 

__attribute__((used)) static u_int32_t
cpcht_read_config(device_t dev, u_int bus, u_int slot, u_int func, u_int reg,
    int width)
{
	struct		cpcht_softc *sc;
	vm_offset_t	caoff;

	sc = device_get_softc(dev);
	caoff = sc->sc_data + 
		(((((slot & 0x1f) << 3) | (func & 0x07)) << 8) | reg);

	if (bus == 0 && (!(sc->sc_populated_slots & (1 << slot)) || func > 0))
		return (0xffffffff);

	if (bus > 0)
		caoff += 0x01000000UL + (bus << 16);

	switch (width) {
	case 1:
		return (in8rb(caoff));
		break;
	case 2:
		return (in16rb(caoff));
		break;
	case 4:
		return (in32rb(caoff));
		break;
	}

	return (0xffffffff);
}