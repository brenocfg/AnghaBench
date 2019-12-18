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
typedef  int uint16_t ;
struct agp_i810_softc {int gtt_mappable_entries; int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I830_GCC1 ; 
 int AGP_I830_GCC1_GMASIZE ; 
 int AGP_I830_GCC1_GMASIZE_64 ; 
 int AGP_PAGE_SHIFT ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_i830_get_gtt_mappable_entries(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t ap;
	uint16_t gmch_ctl;

	sc = device_get_softc(dev);
	gmch_ctl = pci_read_config(sc->bdev, AGP_I830_GCC1, 2);
	if ((gmch_ctl & AGP_I830_GCC1_GMASIZE) == AGP_I830_GCC1_GMASIZE_64)
		ap = 64;
	else
		ap = 128;
	sc->gtt_mappable_entries = (ap * 1024 * 1024) >> AGP_PAGE_SHIFT;
	return (0);
}