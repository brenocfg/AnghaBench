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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  q; } ;
struct msr_info {TYPE_1__ reg; int /*<<< orphan*/  msr_no; } ;
typedef  int /*<<< orphan*/  rv ;

/* Variables and functions */
 int /*<<< orphan*/  __rdmsr_on_cpu ; 
 int /*<<< orphan*/  memset (struct msr_info*,int /*<<< orphan*/ ,int) ; 
 int smp_call_function_single (unsigned int,int /*<<< orphan*/ ,struct msr_info*,int) ; 

int rdmsrl_on_cpu(unsigned int cpu, u32 msr_no, u64 *q)
{
	int err;
	struct msr_info rv;

	memset(&rv, 0, sizeof(rv));

	rv.msr_no = msr_no;
	err = smp_call_function_single(cpu, __rdmsr_on_cpu, &rv, 1);
	*q = rv.reg.q;

	return err;
}