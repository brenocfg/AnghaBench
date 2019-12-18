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
 int /*<<< orphan*/  NDS32_SR_PFM_CTL ; 
 int* PFM_CTL_OVF ; 
 int __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 nds32_pfm_getreset_flags(void)
{
	/* Read overflow status */
	u32 val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 old_val = val;

	/* Write overflow bit to clear status, and others keep it 0 */
	u32 ov_flag = PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2];

	__nds32__mtsr(val | ov_flag, NDS32_SR_PFM_CTL);

	return old_val;
}