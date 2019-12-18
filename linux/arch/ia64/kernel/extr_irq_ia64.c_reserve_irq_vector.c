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
 int /*<<< orphan*/  CPU_MASK_ALL ; 
 int EINVAL ; 
 int IA64_FIRST_DEVICE_VECTOR ; 
 int IA64_LAST_DEVICE_VECTOR ; 
 int /*<<< orphan*/  bind_irq_vector (int,int,int /*<<< orphan*/ ) ; 

int
reserve_irq_vector (int vector)
{
	if (vector < IA64_FIRST_DEVICE_VECTOR ||
	    vector > IA64_LAST_DEVICE_VECTOR)
		return -EINVAL;
	return !!bind_irq_vector(vector, vector, CPU_MASK_ALL);
}