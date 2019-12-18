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
 int STBCR_MSTP ; 
 int /*<<< orphan*/  STBCR_REG (unsigned int) ; 
 int STBCR_RESET ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void shx3_update_boot_vector(unsigned int cpu)
{
	__raw_writel(STBCR_MSTP, STBCR_REG(cpu));
	while (!(__raw_readl(STBCR_REG(cpu)) & STBCR_MSTP))
		cpu_relax();
	__raw_writel(STBCR_RESET, STBCR_REG(cpu));
}