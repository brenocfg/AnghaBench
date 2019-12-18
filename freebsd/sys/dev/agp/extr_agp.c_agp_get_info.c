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
struct agp_softc {int /*<<< orphan*/  as_allocated; int /*<<< orphan*/  as_maxmem; int /*<<< orphan*/ * as_aperture; } ;
struct agp_info {int /*<<< orphan*/  ai_memory_used; int /*<<< orphan*/  ai_memory_allowed; int /*<<< orphan*/  ai_aperture_size; int /*<<< orphan*/  ai_aperture_base; int /*<<< orphan*/  ai_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_STATUS ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 

void
agp_get_info(device_t dev, struct agp_info *info)
{
	struct agp_softc *sc = device_get_softc(dev);

	info->ai_mode =
		pci_read_config(dev, agp_find_caps(dev) + AGP_STATUS, 4);
	if (sc->as_aperture != NULL)
		info->ai_aperture_base = rman_get_start(sc->as_aperture);
	else
		info->ai_aperture_base = 0;
	info->ai_aperture_size = AGP_GET_APERTURE(dev);
	info->ai_memory_allowed = sc->as_maxmem;
	info->ai_memory_used = sc->as_allocated;
}