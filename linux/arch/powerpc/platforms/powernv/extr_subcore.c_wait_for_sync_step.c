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
struct TYPE_2__ {int step; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  mb () ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  split_state ; 
 int threads_per_core ; 

__attribute__((used)) static void wait_for_sync_step(int step)
{
	int i, cpu = smp_processor_id();

	for (i = cpu + 1; i < cpu + threads_per_core; i++)
		while(per_cpu(split_state, i).step < step)
			barrier();

	/* Order the wait loop vs any subsequent loads/stores. */
	mb();
}