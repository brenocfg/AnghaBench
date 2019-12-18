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
 int /*<<< orphan*/ ** vfp_current_hw_state ; 

__attribute__((used)) static int vfp_dying_cpu(unsigned int cpu)
{
	vfp_current_hw_state[cpu] = NULL;
	return 0;
}