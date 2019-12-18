#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmio_hpte_cache_entry {int dummy; } ;
struct TYPE_3__ {unsigned int index; struct mmio_hpte_cache_entry* entry; } ;
struct TYPE_4__ {TYPE_1__ mmio_cache; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 unsigned int MMIO_HPTE_CACHE_SIZE ; 

__attribute__((used)) static struct mmio_hpte_cache_entry *
			next_mmio_cache_entry(struct kvm_vcpu *vcpu)
{
	unsigned int index = vcpu->arch.mmio_cache.index;

	vcpu->arch.mmio_cache.index++;
	if (vcpu->arch.mmio_cache.index == MMIO_HPTE_CACHE_SIZE)
		vcpu->arch.mmio_cache.index = 0;

	return &vcpu->arch.mmio_cache.entry[index];
}