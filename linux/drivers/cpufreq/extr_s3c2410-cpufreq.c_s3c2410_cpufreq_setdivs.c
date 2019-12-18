#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int h_divisor; int p_divisor; } ;
struct s3c_cpufreq_config {TYPE_1__ divs; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_CLKDIVN ; 
 int /*<<< orphan*/  S3C2410_CLKDIVN_HDIVN ; 
 int /*<<< orphan*/  S3C2410_CLKDIVN_PDIVN ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2410_cpufreq_setdivs(struct s3c_cpufreq_config *cfg)
{
	u32 clkdiv = 0;

	if (cfg->divs.h_divisor == 2)
		clkdiv |= S3C2410_CLKDIVN_HDIVN;

	if (cfg->divs.p_divisor != cfg->divs.h_divisor)
		clkdiv |= S3C2410_CLKDIVN_PDIVN;

	__raw_writel(clkdiv, S3C2410_CLKDIVN);
}