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
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
agp_sis_get_aperture(device_t dev)
{
	int gws;

	/*
	 * The aperture size is equal to 4M<<gws.
	 */
	gws = (pci_read_config(dev, AGP_SIS_WINCTRL, 1) & 0x70) >> 4;
	return (4*1024*1024) << gws;
}