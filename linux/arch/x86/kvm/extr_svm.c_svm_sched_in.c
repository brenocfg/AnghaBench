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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ pause_filter_thresh ; 
 int /*<<< orphan*/  shrink_ple_window (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_sched_in(struct kvm_vcpu *vcpu, int cpu)
{
	if (pause_filter_thresh)
		shrink_ple_window(vcpu);
}