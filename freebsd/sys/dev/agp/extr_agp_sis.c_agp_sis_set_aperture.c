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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_SIS_WINCTRL ; 
 int EINVAL ; 
 int ffs (int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_sis_set_aperture(device_t dev, u_int32_t aperture)
{
	int gws;

	/*
	 * Check for a power of two and make sure its within the
	 * programmable range.
	 */
	if (aperture & (aperture - 1)
	    || aperture < 4*1024*1024
	    || aperture > 256*1024*1024)
		return EINVAL;

	gws = ffs(aperture / 4*1024*1024) - 1;
	
	pci_write_config(dev, AGP_SIS_WINCTRL,
			 ((pci_read_config(dev, AGP_SIS_WINCTRL, 1) & ~0x70)
			  | gws << 4), 1);

	return 0;
}