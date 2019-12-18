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
struct uninorth_softc {int /*<<< orphan*/  sc_cfg_mtx; scalar_t__ sc_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct uninorth_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int in16rb (scalar_t__) ; 
 int in32rb (scalar_t__) ; 
 int in8rb (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ uninorth_enable_config (struct uninorth_softc*,int,int,int,int) ; 

__attribute__((used)) static u_int32_t
uninorth_read_config(device_t dev, u_int bus, u_int slot, u_int func, u_int reg,
    int width)
{
	struct		uninorth_softc *sc;
	vm_offset_t	caoff;
	u_int32_t	val;

	sc = device_get_softc(dev);
	caoff = sc->sc_data + (reg & 0x07);
	val = 0xffffffff;

	mtx_lock_spin(&sc->sc_cfg_mtx);
	if (uninorth_enable_config(sc, bus, slot, func, reg) != 0) {
		switch (width) {
		case 1: 
			val = in8rb(caoff);
			break;
		case 2:
			val = in16rb(caoff);
			break;
		case 4:
			val = in32rb(caoff);
			break;
		}
	}
	mtx_unlock_spin(&sc->sc_cfg_mtx);

	return (val);
}