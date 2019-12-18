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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_unmap_hva (struct kvm*,unsigned long) ; 

int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
{
	/* kvm_unmap_hva flushes everything anyways */
	kvm_unmap_hva(kvm, start);

	return 0;
}