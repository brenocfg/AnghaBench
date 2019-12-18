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
struct op_msrs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cccr_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCR_SET_ENABLE (unsigned int) ; 
 size_t VIRT_CTR (unsigned int,int) ; 
 unsigned int get_stagger () ; 
 int num_counters ; 
 TYPE_1__* p4_counters ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * reset_value ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void p4_start(struct op_msrs const * const msrs)
{
	unsigned int low, high, stag;
	int i;

	stag = get_stagger();

	for (i = 0; i < num_counters; ++i) {
		if (!reset_value[i])
			continue;
		rdmsr(p4_counters[VIRT_CTR(stag, i)].cccr_address, low, high);
		CCCR_SET_ENABLE(low);
		wrmsr(p4_counters[VIRT_CTR(stag, i)].cccr_address, low, high);
	}
}