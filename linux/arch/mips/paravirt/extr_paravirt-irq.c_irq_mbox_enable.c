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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_mbox_all (struct irq_data*,scalar_t__) ; 
 scalar_t__ mips_irq_chip ; 
 scalar_t__ mips_irq_chip_reg_en_w1s ; 

__attribute__((used)) static void irq_mbox_enable(struct irq_data *data)
{
	irq_mbox_all(data, mips_irq_chip + mips_irq_chip_reg_en_w1s + sizeof(u32));
}