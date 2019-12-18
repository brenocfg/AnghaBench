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

/* Variables and functions */
 int /*<<< orphan*/  RESET_REG (unsigned int) ; 
 unsigned long STBCR_LTSLP ; 
 unsigned long STBCR_MSTP ; 
 int /*<<< orphan*/  STBCR_REG (unsigned int) ; 
 unsigned long STBCR_RESET ; 
 scalar_t__ __in_29bit_mode () ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long virt_to_phys (unsigned long) ; 

__attribute__((used)) static void shx3_start_cpu(unsigned int cpu, unsigned long entry_point)
{
	if (__in_29bit_mode())
		__raw_writel(entry_point, RESET_REG(cpu));
	else
		__raw_writel(virt_to_phys(entry_point), RESET_REG(cpu));

	if (!(__raw_readl(STBCR_REG(cpu)) & STBCR_MSTP))
		__raw_writel(STBCR_MSTP, STBCR_REG(cpu));

	while (!(__raw_readl(STBCR_REG(cpu)) & STBCR_MSTP))
		cpu_relax();

	/* Start up secondary processor by sending a reset */
	__raw_writel(STBCR_RESET | STBCR_LTSLP, STBCR_REG(cpu));
}