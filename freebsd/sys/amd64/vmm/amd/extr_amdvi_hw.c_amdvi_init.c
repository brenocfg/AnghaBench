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

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  amdvi_enable_user ; 
 int ivhd_count ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
amdvi_init(void)
{
	if (!ivhd_count) {
		return (EIO);
	}
	if (!amdvi_enable_user && ivhd_count) {
		printf("bhyve: Found %d AMD-Vi/IOMMU device(s), "
		    	"use hw.vmm.amdvi.enable=1 to enable pass-through.\n",
		    ivhd_count);
		return (EINVAL);
	}
	return (0);
}