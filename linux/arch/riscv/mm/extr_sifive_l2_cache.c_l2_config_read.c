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
typedef  int uint64_t ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ SIFIVE_L2_CONFIG ; 
 scalar_t__ SIFIVE_L2_WAYENABLE ; 
 scalar_t__ l2_base ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void l2_config_read(void)
{
	u32 regval, val;

	regval = readl(l2_base + SIFIVE_L2_CONFIG);
	val = regval & 0xFF;
	pr_info("L2CACHE: No. of Banks in the cache: %d\n", val);
	val = (regval & 0xFF00) >> 8;
	pr_info("L2CACHE: No. of ways per bank: %d\n", val);
	val = (regval & 0xFF0000) >> 16;
	pr_info("L2CACHE: Sets per bank: %llu\n", (uint64_t)1 << val);
	val = (regval & 0xFF000000) >> 24;
	pr_info("L2CACHE: Bytes per cache block: %llu\n", (uint64_t)1 << val);

	regval = readl(l2_base + SIFIVE_L2_WAYENABLE);
	pr_info("L2CACHE: Index of the largest way enabled: %d\n", regval);
}