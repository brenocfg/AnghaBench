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

/* Variables and functions */
 int /*<<< orphan*/  ST0_BEV ; 
 unsigned int STATUSF_IP2 ; 
 scalar_t__ ebase ; 
 int /*<<< orphan*/  irq_cpu_online () ; 
 unsigned int set_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_ebase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_status (unsigned int) ; 

__attribute__((used)) static void paravirt_init_secondary(void)
{
	unsigned int sr;

	sr = set_c0_status(ST0_BEV);
	write_c0_ebase((u32)ebase);

	sr |= STATUSF_IP2; /* Interrupt controller on IP2 */
	write_c0_status(sr);

	irq_cpu_online();
}