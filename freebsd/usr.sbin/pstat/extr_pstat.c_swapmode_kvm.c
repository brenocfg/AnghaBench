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

/* Variables and functions */
 int /*<<< orphan*/  SWIF_DEV_PREFIX ; 
 int /*<<< orphan*/  kd ; 
 int kvm_getswapinfo (int /*<<< orphan*/ ,struct kvm_swap*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_swap (struct kvm_swap*) ; 
 int /*<<< orphan*/  print_swap_header () ; 
 int /*<<< orphan*/  print_swap_total () ; 

__attribute__((used)) static void
swapmode_kvm(void)
{
	struct kvm_swap kswap[16];
	int i, n;

	n = kvm_getswapinfo(kd, kswap, sizeof kswap / sizeof kswap[0],
	    SWIF_DEV_PREFIX);

	print_swap_header();
	for (i = 0; i < n; ++i)
		print_swap(&kswap[i]);
	print_swap_total();
}