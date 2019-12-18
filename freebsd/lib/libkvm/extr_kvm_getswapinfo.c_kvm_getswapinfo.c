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
struct kvm_swap {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 scalar_t__ ISALIVE (int /*<<< orphan*/ *) ; 
 int kvm_getswapinfo_kvm (int /*<<< orphan*/ *,struct kvm_swap*,int,int) ; 
 int kvm_getswapinfo_sysctl (int /*<<< orphan*/ *,struct kvm_swap*,int,int) ; 
 scalar_t__ kvm_swap_nl_cached ; 

int
kvm_getswapinfo(kvm_t *kd, struct kvm_swap *swap_ary, int swap_max, int flags)
{

	/*
	 * clear cache
	 */
	if (kd == NULL) {
		kvm_swap_nl_cached = 0;
		return(0);
	}

	if (ISALIVE(kd)) {
		return kvm_getswapinfo_sysctl(kd, swap_ary, swap_max, flags);
	} else {
		return kvm_getswapinfo_kvm(kd, swap_ary, swap_max, flags);
	}
}