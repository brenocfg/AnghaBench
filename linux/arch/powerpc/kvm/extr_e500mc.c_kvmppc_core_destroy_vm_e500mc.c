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
struct TYPE_2__ {int lpid; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_free_lpid (int) ; 
 int threads_per_core ; 

__attribute__((used)) static void kvmppc_core_destroy_vm_e500mc(struct kvm *kvm)
{
	int lpid = kvm->arch.lpid;

	if (threads_per_core == 2)
		lpid >>= 1;

	kvmppc_free_lpid(lpid);
}