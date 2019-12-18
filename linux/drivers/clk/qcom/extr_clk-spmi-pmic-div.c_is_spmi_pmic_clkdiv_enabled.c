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
struct clkdiv {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ REG_EN_CTL ; 
 unsigned int REG_EN_MASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static bool is_spmi_pmic_clkdiv_enabled(struct clkdiv *clkdiv)
{
	unsigned int val = 0;

	regmap_read(clkdiv->regmap, clkdiv->base + REG_EN_CTL, &val);

	return val & REG_EN_MASK;
}