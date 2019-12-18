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
 int /*<<< orphan*/  end_local_APIC_setup () ; 
 int /*<<< orphan*/  setup_local_APIC () ; 

void apic_ap_setup(void)
{
	setup_local_APIC();
	end_local_APIC_setup();
}