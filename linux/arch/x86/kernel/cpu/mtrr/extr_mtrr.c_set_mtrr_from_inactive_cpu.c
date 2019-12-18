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
struct set_mtrr_data {unsigned int smp_reg; unsigned long smp_base; unsigned long smp_size; int /*<<< orphan*/  smp_type; } ;
typedef  int /*<<< orphan*/  mtrr_type ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_callout_mask ; 
 int /*<<< orphan*/  mtrr_rendezvous_handler ; 
 int /*<<< orphan*/  stop_machine_from_inactive_cpu (int /*<<< orphan*/ ,struct set_mtrr_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_mtrr_from_inactive_cpu(unsigned int reg, unsigned long base,
				      unsigned long size, mtrr_type type)
{
	struct set_mtrr_data data = { .smp_reg = reg,
				      .smp_base = base,
				      .smp_size = size,
				      .smp_type = type
				    };

	stop_machine_from_inactive_cpu(mtrr_rendezvous_handler, &data,
				       cpu_callout_mask);
}