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
struct TYPE_2__ {int /*<<< orphan*/  wdt_timer; int /*<<< orphan*/  wdt_lock; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBSR_MRR ; 
 int /*<<< orphan*/  SPRN_DBSR ; 
 int /*<<< orphan*/  kvmppc_watchdog_func ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvmppc_subarch_vcpu_init(struct kvm_vcpu *vcpu)
{
	/* setup watchdog timer once */
	spin_lock_init(&vcpu->arch.wdt_lock);
	timer_setup(&vcpu->arch.wdt_timer, kvmppc_watchdog_func, 0);

	/*
	 * Clear DBSR.MRR to avoid guest debug interrupt as
	 * this is of host interest
	 */
	mtspr(SPRN_DBSR, DBSR_MRR);
	return 0;
}