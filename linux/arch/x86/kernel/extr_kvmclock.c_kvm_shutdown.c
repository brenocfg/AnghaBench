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
 int /*<<< orphan*/  kvm_disable_steal_time () ; 
 int /*<<< orphan*/  msr_kvm_system_time ; 
 int /*<<< orphan*/  native_machine_shutdown () ; 
 int /*<<< orphan*/  native_write_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_shutdown(void)
{
	native_write_msr(msr_kvm_system_time, 0, 0);
	kvm_disable_steal_time();
	native_machine_shutdown();
}