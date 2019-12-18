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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __cpa_flush_all ; 
 int /*<<< orphan*/  early_boot_irqs_disabled ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void cpa_flush_all(unsigned long cache)
{
	BUG_ON(irqs_disabled() && !early_boot_irqs_disabled);

	on_each_cpu(__cpa_flush_all, (void *) cache, 1);
}