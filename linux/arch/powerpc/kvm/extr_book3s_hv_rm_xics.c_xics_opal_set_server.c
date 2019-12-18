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
 int /*<<< orphan*/  DEFAULT_PRIORITY ; 
 int get_hard_smp_processor_id (int) ; 
 int opal_set_xive (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xics_opal_set_server(unsigned int hw_irq, int server_cpu)
{
	unsigned int mangle_cpu = get_hard_smp_processor_id(server_cpu) << 2;

	return opal_set_xive(hw_irq, mangle_cpu, DEFAULT_PRIORITY);
}