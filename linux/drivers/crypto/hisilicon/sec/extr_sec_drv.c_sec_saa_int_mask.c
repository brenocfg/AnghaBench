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
struct sec_dev_info {scalar_t__* regs; } ;

/* Variables and functions */
 size_t SEC_SAA ; 
 int SEC_SAA_ADDR_SIZE ; 
 scalar_t__ SEC_SAA_BASE ; 
 scalar_t__ SEC_ST_INTMSK1_REG ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sec_saa_int_mask(struct sec_dev_info *info, u32 saa_indx,
			     u32 saa_int_mask)
{
	writel_relaxed(saa_int_mask,
		       info->regs[SEC_SAA] + SEC_SAA_BASE + SEC_ST_INTMSK1_REG +
		       saa_indx * SEC_SAA_ADDR_SIZE);
}