#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum ipi_message_type { ____Placeholder_ipi_message_type } ipi_message_type ;
struct TYPE_2__ {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int cpuid_to_hartid_map (int) ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 TYPE_1__* ipi_data ; 
 int /*<<< orphan*/  sbi_send_ipi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void send_ipi_single(int cpu, enum ipi_message_type op)
{
	int hartid = cpuid_to_hartid_map(cpu);

	smp_mb__before_atomic();
	set_bit(op, &ipi_data[cpu].bits);
	smp_mb__after_atomic();

	sbi_send_ipi(cpumask_bits(cpumask_of(hartid)));
}