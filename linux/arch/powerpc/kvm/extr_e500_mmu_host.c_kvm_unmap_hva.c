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
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int /*<<< orphan*/  trace_kvm_unmap_hva (unsigned long) ; 

__attribute__((used)) static int kvm_unmap_hva(struct kvm *kvm, unsigned long hva)
{
	trace_kvm_unmap_hva(hva);

	/*
	 * Flush all shadow tlb entries everywhere. This is slow, but
	 * we are 100% sure that we catch the to be unmapped page
	 */
	kvm_flush_remote_tlbs(kvm);

	return 0;
}