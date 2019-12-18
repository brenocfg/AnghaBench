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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_IENABLE ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,int) ; 
 int ienable ; 

__attribute__((used)) static void chip_unmask(struct irq_data *d)
{
	ienable |= (1 << d->hwirq);
	WRCTL(CTL_IENABLE, ienable);
}