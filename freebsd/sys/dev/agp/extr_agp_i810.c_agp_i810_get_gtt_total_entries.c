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
struct agp_i810_softc {int /*<<< orphan*/  gtt_mappable_entries; int /*<<< orphan*/  gtt_total_entries; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i810_get_gtt_total_entries(device_t dev)
{
	struct agp_i810_softc *sc;

	sc = device_get_softc(dev);
	sc->gtt_total_entries = sc->gtt_mappable_entries;
	return (0);
}