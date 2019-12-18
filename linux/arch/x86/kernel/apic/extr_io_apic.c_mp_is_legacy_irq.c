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
 int nr_legacy_irqs () ; 

__attribute__((used)) static inline bool mp_is_legacy_irq(int irq)
{
	return irq >= 0 && irq < nr_legacy_irqs();
}