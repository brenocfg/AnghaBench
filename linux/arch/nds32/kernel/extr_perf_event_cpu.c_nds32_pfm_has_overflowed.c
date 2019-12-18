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
 int* PFM_CTL_OVF ; 

__attribute__((used)) static inline int nds32_pfm_has_overflowed(u32 pfm)
{
	u32 ov_flag = PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2];

	return pfm & ov_flag;
}