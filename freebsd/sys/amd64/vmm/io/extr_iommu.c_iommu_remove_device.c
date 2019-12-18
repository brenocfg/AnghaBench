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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_REMOVE_DEVICE (void*,int /*<<< orphan*/ ) ; 

void
iommu_remove_device(void *dom, uint16_t rid)
{

	IOMMU_REMOVE_DEVICE(dom, rid);
}