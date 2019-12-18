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
struct sec_dev_info {scalar_t__* regs; } ;

/* Variables and functions */
 scalar_t__ SEC_Q_VMID_CFG_REG (int) ; 
 size_t SEC_SAA ; 
 int SEC_SID ; 
 int SEC_VMID ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sec_streamid(struct sec_dev_info *info, int i)
{
	#define SEC_SID 0x600
	#define SEC_VMID 0

	writel_relaxed((SEC_VMID | ((SEC_SID & 0xffff) << 8)),
		       info->regs[SEC_SAA] + SEC_Q_VMID_CFG_REG(i));
}