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
struct agp_i810_softc {int gtt_mappable_entries; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 int AGP_PAGE_SHIFT ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i915_get_gtt_mappable_entries(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t ap;

	sc = device_get_softc(dev);
	ap = AGP_GET_APERTURE(dev);
	sc->gtt_mappable_entries = ap >> AGP_PAGE_SHIFT;
	return (0);
}