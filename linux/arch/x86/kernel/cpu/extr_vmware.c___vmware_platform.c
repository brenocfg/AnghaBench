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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GETVERSION ; 
 int /*<<< orphan*/  VMWARE_CMD (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ VMWARE_HYPERVISOR_MAGIC ; 

__attribute__((used)) static inline int __vmware_platform(void)
{
	uint32_t eax, ebx, ecx, edx;
	VMWARE_CMD(GETVERSION, eax, ebx, ecx, edx);
	return eax != (uint32_t)-1 && ebx == VMWARE_HYPERVISOR_MAGIC;
}