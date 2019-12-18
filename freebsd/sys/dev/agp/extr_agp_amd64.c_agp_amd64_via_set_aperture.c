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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP3_VIA_APSIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_amd64_via_set_aperture(device_t dev, uint32_t aperture)
{
	uint32_t apsize;

	apsize = ((aperture - 1) >> 20) ^ 0xff;
	if ((((apsize ^ 0xff) << 20) | ((1 << 20) - 1)) + 1 != aperture)
		return (EINVAL);
	pci_cfgregwrite(0, 1, 0, AGP3_VIA_APSIZE, apsize, 1);

	return (0);
}