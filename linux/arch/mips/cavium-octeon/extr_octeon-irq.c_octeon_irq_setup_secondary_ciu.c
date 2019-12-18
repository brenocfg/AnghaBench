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
 int STATUSF_IP2 ; 
 int STATUSF_IP3 ; 
 int STATUSF_IP4 ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 
 int /*<<< orphan*/  octeon_irq_init_ciu_percpu () ; 
 int /*<<< orphan*/  octeon_irq_percpu_enable () ; 
 scalar_t__ octeon_irq_use_ip4 ; 
 int /*<<< orphan*/  set_c0_status (int) ; 

__attribute__((used)) static void octeon_irq_setup_secondary_ciu(void)
{
	octeon_irq_init_ciu_percpu();
	octeon_irq_percpu_enable();

	/* Enable the CIU lines */
	set_c0_status(STATUSF_IP3 | STATUSF_IP2);
	if (octeon_irq_use_ip4)
		set_c0_status(STATUSF_IP4);
	else
		clear_c0_status(STATUSF_IP4);
}