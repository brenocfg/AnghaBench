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
typedef  int uint32_t ;
typedef  int u_int ;
struct vmd_softc {int /*<<< orphan*/  vmd_bhandle; int /*<<< orphan*/  vmd_btag; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vmd_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
vmd_read_config(device_t dev, u_int b, u_int s, u_int f, u_int reg, int width)
{

	struct vmd_softc *sc;
	bus_addr_t offset;

	offset = (b << 20) + (s << 15) + (f << 12) + reg;
	sc = device_get_softc(dev);
	switch(width) {
	case 4:
		return (bus_space_read_4(sc->vmd_btag, sc->vmd_bhandle,
		    offset));
	case 2:
		return (bus_space_read_2(sc->vmd_btag, sc->vmd_bhandle,
		    offset));
	case 1:
		return (bus_space_read_1(sc->vmd_btag, sc->vmd_bhandle,
		    offset));
	default:
		KASSERT(1, ("Invalid width requested"));
		return (0xffffffff);
	}
}