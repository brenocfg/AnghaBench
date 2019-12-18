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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_NVIDIA_0_APSIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_nvidia_set_aperture(device_t dev, u_int32_t aperture)
{
	u_int8_t val;
	u_int8_t key;

	switch (aperture) {
	case (512 * 1024 * 1024): key = 0; break;
	case (256 * 1024 * 1024): key = 8; break;
	case (128 * 1024 * 1024): key = 12; break;
	case (64 * 1024 * 1024): key = 14; break;
	case (32 * 1024 * 1024): key = 15; break;
	default:
		device_printf(dev, "Invalid aperture size (%dMb)\n",
				aperture / 1024 / 1024);
		return (EINVAL);
	}
	val = pci_read_config(dev, AGP_NVIDIA_0_APSIZE, 1);
	pci_write_config(dev, AGP_NVIDIA_0_APSIZE, ((val & ~0x0f) | key), 1);

	return (0);
}