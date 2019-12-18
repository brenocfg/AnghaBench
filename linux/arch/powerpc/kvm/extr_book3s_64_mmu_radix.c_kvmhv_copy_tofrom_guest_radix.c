#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pid; TYPE_1__* nested; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_3__* kvm; } ;
typedef  int gva_t ;
struct TYPE_6__ {int lpid; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;
struct TYPE_5__ {int shadow_lpid; } ;

/* Variables and functions */
 long EINVAL ; 
 long __kvmhv_copy_tofrom_guest_radix (int,int,int,void*,void*,unsigned long) ; 

__attribute__((used)) static long kvmhv_copy_tofrom_guest_radix(struct kvm_vcpu *vcpu, gva_t eaddr,
					  void *to, void *from, unsigned long n)
{
	int lpid = vcpu->kvm->arch.lpid;
	int pid = vcpu->arch.pid;

	/* This would cause a data segment intr so don't allow the access */
	if (eaddr & (0x3FFUL << 52))
		return -EINVAL;

	/* Should we be using the nested lpid */
	if (vcpu->arch.nested)
		lpid = vcpu->arch.nested->shadow_lpid;

	/* If accessing quadrant 3 then pid is expected to be 0 */
	if (((eaddr >> 62) & 0x3) == 0x3)
		pid = 0;

	eaddr &= ~(0xFFFUL << 52);

	return __kvmhv_copy_tofrom_guest_radix(lpid, pid, eaddr, to, from, n);
}