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
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_vcpu ; 
 unsigned long kvm_rip_read (scalar_t__) ; 

__attribute__((used)) static unsigned long kvm_get_guest_ip(void)
{
	unsigned long ip = 0;

	if (__this_cpu_read(current_vcpu))
		ip = kvm_rip_read(__this_cpu_read(current_vcpu));

	return ip;
}