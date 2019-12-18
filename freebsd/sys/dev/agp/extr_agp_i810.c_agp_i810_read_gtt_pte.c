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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int ;
struct agp_i810_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_I810_GTT ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
agp_i810_read_gtt_pte(device_t dev, u_int index)
{
	struct agp_i810_softc *sc;
	u_int32_t pte;

	sc = device_get_softc(dev);
	pte = bus_read_4(sc->sc_res[0], AGP_I810_GTT + index * 4);
	return (pte);
}