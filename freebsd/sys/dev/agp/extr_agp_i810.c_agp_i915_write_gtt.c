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
typedef  int u_int ;
struct agp_i810_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_AGP_I810 ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
agp_i915_write_gtt(device_t dev, u_int index, uint32_t pte)
{
	struct agp_i810_softc *sc;

	sc = device_get_softc(dev);
	bus_write_4(sc->sc_res[1], index * 4, pte);
	CTR2(KTR_AGP_I810, "915_pte %x %x", index, pte);
}