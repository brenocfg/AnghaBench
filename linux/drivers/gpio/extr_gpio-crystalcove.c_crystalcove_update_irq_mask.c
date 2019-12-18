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
typedef  int /*<<< orphan*/  u8 ;
struct crystalcove_gpio {int /*<<< orphan*/  regmap; scalar_t__ set_irq_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MGPIO0IRQS0 ; 
 int /*<<< orphan*/  MGPIO1IRQS0 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void crystalcove_update_irq_mask(struct crystalcove_gpio *cg,
					int gpio)
{
	u8 mirqs0 = gpio < 8 ? MGPIO0IRQS0 : MGPIO1IRQS0;
	int mask = BIT(gpio % 8);

	if (cg->set_irq_mask)
		regmap_update_bits(cg->regmap, mirqs0, mask, mask);
	else
		regmap_update_bits(cg->regmap, mirqs0, mask, 0);
}