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
 int /*<<< orphan*/  AGP_AMD751_APCTRL ; 
 int EINVAL ; 
 int ffs (int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_amd_set_aperture(device_t dev, u_int32_t aperture)
{
	int vas;

	/*
	 * Check for a power of two and make sure its within the
	 * programmable range.
	 */
	if (aperture & (aperture - 1)
	    || aperture < 32*1024*1024
	    || aperture > 2U*1024*1024*1024)
		return EINVAL;

	vas = ffs(aperture / 32*1024*1024) - 1;
	
	/* 
	 * While the size register is bits 1-3 of APCTRL, bit 0 must be
	 * set for the size value to be 'valid'
	 */
	pci_write_config(dev, AGP_AMD751_APCTRL,
			 (((pci_read_config(dev, AGP_AMD751_APCTRL, 1) & ~0x06)
			  | ((vas << 1) | 1))), 1);

	return 0;
}