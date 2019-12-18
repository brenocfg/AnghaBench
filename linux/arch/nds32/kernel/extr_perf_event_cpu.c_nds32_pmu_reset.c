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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_PFMC0 ; 
 int /*<<< orphan*/  NDS32_SR_PFMC1 ; 
 int /*<<< orphan*/  NDS32_SR_PFMC2 ; 
 int /*<<< orphan*/  NDS32_SR_PFM_CTL ; 
 int* PFM_CTL_OVF ; 
 int /*<<< orphan*/  __nds32__mtsr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nds32_pmu_reset(void *info)
{
	u32 val = 0;

	val |= (PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr(val, NDS32_SR_PFM_CTL);
	__nds32__mtsr(0, NDS32_SR_PFM_CTL);
	__nds32__mtsr(0, NDS32_SR_PFMC0);
	__nds32__mtsr(0, NDS32_SR_PFMC1);
	__nds32__mtsr(0, NDS32_SR_PFMC2);
}