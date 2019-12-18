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

/* Variables and functions */
 int /*<<< orphan*/  VMCS_GUEST_SS_ACCESS_RIGHTS ; 
 int vmcs_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmx_cpl(void)
{
	uint32_t ssar;

	ssar = vmcs_read(VMCS_GUEST_SS_ACCESS_RIGHTS);
	return ((ssar >> 5) & 0x3);
}