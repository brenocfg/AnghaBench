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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_SR ; 
 unsigned int PLL_STATUS_MASK (int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline bool clk_pll_ready(struct regmap *regmap, int id)
{
	unsigned int status;

	regmap_read(regmap, AT91_PMC_SR, &status);

	return status & PLL_STATUS_MASK(id) ? 1 : 0;
}