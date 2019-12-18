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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int drm_device_find_capability (struct drm_device*,int /*<<< orphan*/ ) ; 

int
drm_pci_device_is_pcie(struct drm_device *dev)
{

	return (drm_device_find_capability(dev, PCIY_EXPRESS));
}