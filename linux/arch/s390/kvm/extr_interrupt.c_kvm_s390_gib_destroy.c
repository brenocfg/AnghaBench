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
 int /*<<< orphan*/  chsc_sgib (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/ * gib ; 
 int /*<<< orphan*/  gib_alert_irq ; 
 int /*<<< orphan*/  unregister_adapter_interrupt (int /*<<< orphan*/ *) ; 

void kvm_s390_gib_destroy(void)
{
	if (!gib)
		return;
	chsc_sgib(0);
	unregister_adapter_interrupt(&gib_alert_irq);
	free_page((unsigned long)gib);
	gib = NULL;
}