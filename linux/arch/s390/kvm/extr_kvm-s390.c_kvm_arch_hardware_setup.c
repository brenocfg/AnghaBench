#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ gmap_notifier ; 
 int /*<<< orphan*/  gmap_register_pte_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  kvm_clock_notifier ; 
 int /*<<< orphan*/  kvm_gmap_notifier ; 
 int /*<<< orphan*/  kvm_s390_vsie_gmap_notifier ; 
 int /*<<< orphan*/  s390_epoch_delta_notifier ; 
 TYPE_1__ vsie_gmap_notifier ; 

int kvm_arch_hardware_setup(void)
{
	gmap_notifier.notifier_call = kvm_gmap_notifier;
	gmap_register_pte_notifier(&gmap_notifier);
	vsie_gmap_notifier.notifier_call = kvm_s390_vsie_gmap_notifier;
	gmap_register_pte_notifier(&vsie_gmap_notifier);
	atomic_notifier_chain_register(&s390_epoch_delta_notifier,
				       &kvm_clock_notifier);
	return 0;
}