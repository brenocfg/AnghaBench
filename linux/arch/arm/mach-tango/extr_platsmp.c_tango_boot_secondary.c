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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  tango_set_aux_boot_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tango_start_aux_core (unsigned int) ; 

__attribute__((used)) static int tango_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	tango_set_aux_boot_addr(__pa_symbol(secondary_startup));
	tango_start_aux_core(cpu);
	return 0;
}