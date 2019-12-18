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
typedef  int /*<<< orphan*/  u32 ;
struct pll_data {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  soc_readl (scalar_t__) ; 

__attribute__((used)) static u32 pll_read(struct pll_data *pll, int reg)
{
	return soc_readl(pll->base + reg);
}