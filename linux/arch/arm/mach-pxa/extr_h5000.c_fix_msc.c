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
 int /*<<< orphan*/  MDREFR ; 
 int /*<<< orphan*/  MSC0 ; 
 int /*<<< orphan*/  MSC1 ; 
 int /*<<< orphan*/  MSC2 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fix_msc(void)
{
	__raw_writel(0x129c24f2, MSC0);
	__raw_writel(0x7ff424fa, MSC1);
	__raw_writel(0x7ff47ff4, MSC2);

	__raw_writel(__raw_readl(MDREFR) | 0x02080000, MDREFR);
}