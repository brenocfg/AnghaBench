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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K8_UCODE_UPDATE ; 
 int /*<<< orphan*/  do_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr_safe (int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static void
amd_ucode_wrmsr(void *ucode_ptr)
{
	uint32_t tmp[4];

	wrmsr_safe(MSR_K8_UCODE_UPDATE, (uintptr_t)ucode_ptr);
	do_cpuid(0, tmp);
}