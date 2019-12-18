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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int ;
struct uninorth_softc {int /*<<< orphan*/  sc_cfg_mtx; scalar_t__ sc_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct uninorth_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out16rb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out32rb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out8rb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ uninorth_enable_config (struct uninorth_softc*,int,int,int,int) ; 

__attribute__((used)) static void
uninorth_write_config(device_t dev, u_int bus, u_int slot, u_int func,
    u_int reg, u_int32_t val, int width)
{
	struct		uninorth_softc *sc;
	vm_offset_t	caoff;

	sc = device_get_softc(dev);
	caoff = sc->sc_data + (reg & 0x07);

	mtx_lock_spin(&sc->sc_cfg_mtx);
	if (uninorth_enable_config(sc, bus, slot, func, reg)) {
		switch (width) {
		case 1:
			out8rb(caoff, val);
			break;
		case 2:
			out16rb(caoff, val);
			break;
		case 4:
			out32rb(caoff, val);
			break;
		}
	}
	mtx_unlock_spin(&sc->sc_cfg_mtx);
}