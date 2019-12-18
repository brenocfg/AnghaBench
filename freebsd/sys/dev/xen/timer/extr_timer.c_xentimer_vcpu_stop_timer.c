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
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPUOP_stop_singleshot_timer ; 

__attribute__((used)) static int
xentimer_vcpu_stop_timer(int vcpu)
{

	return (HYPERVISOR_vcpu_op(VCPUOP_stop_singleshot_timer, vcpu, NULL));
}