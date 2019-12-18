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
struct agp_intel_softc {int /*<<< orphan*/  current_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_intel_commit_gatt (int /*<<< orphan*/ ) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct agp_intel_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_intel_resume(device_t dev)
{
	struct agp_intel_softc *sc;
	sc = device_get_softc(dev);
	
	AGP_SET_APERTURE(dev, sc->current_aperture);
	agp_intel_commit_gatt(dev);
	return (bus_generic_resume(dev));
}