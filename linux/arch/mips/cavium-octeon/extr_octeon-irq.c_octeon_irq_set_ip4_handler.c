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
typedef  int /*<<< orphan*/  octeon_irq_ip4_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_irq_ip4 ; 
 int /*<<< orphan*/  octeon_irq_local_enable_ip4 ; 
 int octeon_irq_use_ip4 ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void octeon_irq_set_ip4_handler(octeon_irq_ip4_handler_t h)
{
	octeon_irq_ip4 = h;
	octeon_irq_use_ip4 = true;
	on_each_cpu(octeon_irq_local_enable_ip4, NULL, 1);
}