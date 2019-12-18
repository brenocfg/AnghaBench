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
struct TYPE_4__ {TYPE_1__* apic; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int gpa_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 scalar_t__ kvm_io_bus_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int,void const*) ; 
 int /*<<< orphan*/  kvm_iodevice_write (struct kvm_vcpu*,int /*<<< orphan*/ *,int,int,void const*) ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int min (int,int) ; 

__attribute__((used)) static int vcpu_mmio_write(struct kvm_vcpu *vcpu, gpa_t addr, int len,
			   const void *v)
{
	int handled = 0;
	int n;

	do {
		n = min(len, 8);
		if (!(lapic_in_kernel(vcpu) &&
		      !kvm_iodevice_write(vcpu, &vcpu->arch.apic->dev, addr, n, v))
		    && kvm_io_bus_write(vcpu, KVM_MMIO_BUS, addr, n, v))
			break;
		handled += n;
		addr += n;
		len -= n;
		v += n;
	} while (len);

	return handled;
}