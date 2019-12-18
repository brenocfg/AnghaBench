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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_interrupt_dump_registers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_safe_printf (char*,int) ; 

__attribute__((used)) static void __cvmx_interrupt_default(int irq_number, uint64_t *registers, void *user_arg)
{
    cvmx_safe_printf("cvmx_interrupt_default: Received interrupt %d\n", irq_number);
    __cvmx_interrupt_dump_registers(registers);
}