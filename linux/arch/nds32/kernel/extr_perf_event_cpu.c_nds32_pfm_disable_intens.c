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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_PFM_CTL ; 
 unsigned int* PFM_CTL_IE ; 
 unsigned int* PFM_CTL_OVF ; 
 unsigned int __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_isb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nds32_pfm_disable_intens(int idx)
{
	unsigned int val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 mask = 0;

	mask = PFM_CTL_IE[idx];
	val &= ~mask;
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
	return idx;
}