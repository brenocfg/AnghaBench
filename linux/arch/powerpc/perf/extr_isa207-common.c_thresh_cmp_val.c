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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int MMCRA_THR_CMP_SHIFT ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int p9_MMCRA_THR_CMP_SHIFT ; 

__attribute__((used)) static u64 thresh_cmp_val(u64 value)
{
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		return value << p9_MMCRA_THR_CMP_SHIFT;

	return value << MMCRA_THR_CMP_SHIFT;
}