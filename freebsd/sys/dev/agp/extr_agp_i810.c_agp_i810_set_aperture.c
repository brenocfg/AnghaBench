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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct agp_i810_softc {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_MISCC ; 
 int /*<<< orphan*/  AGP_I810_MISCC_WINSIZE ; 
 int /*<<< orphan*/  AGP_I810_MISCC_WINSIZE_32 ; 
 int /*<<< orphan*/  AGP_I810_MISCC_WINSIZE_64 ; 
 int EINVAL ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_i810_set_aperture(device_t dev, u_int32_t aperture)
{
	struct agp_i810_softc *sc;
	u_int16_t miscc;

	sc = device_get_softc(dev);
	/*
	 * Double check for sanity.
	 */
	if (aperture != 32 * 1024 * 1024 && aperture != 64 * 1024 * 1024) {
		device_printf(dev, "bad aperture size %d\n", aperture);
		return (EINVAL);
	}

	miscc = pci_read_config(sc->bdev, AGP_I810_MISCC, 2);
	miscc &= ~AGP_I810_MISCC_WINSIZE;
	if (aperture == 32 * 1024 * 1024)
		miscc |= AGP_I810_MISCC_WINSIZE_32;
	else
		miscc |= AGP_I810_MISCC_WINSIZE_64;
	
	pci_write_config(sc->bdev, AGP_I810_MISCC, miscc, 2);
	return (0);
}