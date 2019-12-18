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
typedef  scalar_t__ u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 scalar_t__ dart_device_on_pcie (int /*<<< orphan*/ *) ; 
 scalar_t__ dart_is_u4 ; 

__attribute__((used)) static bool iommu_bypass_supported_dart(struct pci_dev *dev, u64 mask)
{
	return dart_is_u4 &&
		dart_device_on_pcie(&dev->dev) &&
		mask >= DMA_BIT_MASK(40);
}