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
typedef  int u32 ;
struct kvmppc_vcore {int arch_compat; unsigned long pcr; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_206 ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EINVAL ; 
 unsigned long PCR_ARCH_205 ; 
 unsigned long PCR_ARCH_206 ; 
 unsigned long PCR_ARCH_207 ; 
 unsigned long PCR_ARCH_300 ; 
 unsigned long PCR_MASK ; 
#define  PVR_ARCH_205 132 
#define  PVR_ARCH_206 131 
#define  PVR_ARCH_206p 130 
#define  PVR_ARCH_207 129 
#define  PVR_ARCH_300 128 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvmppc_set_arch_compat(struct kvm_vcpu *vcpu, u32 arch_compat)
{
	unsigned long host_pcr_bit = 0, guest_pcr_bit = 0;
	struct kvmppc_vcore *vc = vcpu->arch.vcore;

	/* We can (emulate) our own architecture version and anything older */
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		host_pcr_bit = PCR_ARCH_300;
	else if (cpu_has_feature(CPU_FTR_ARCH_207S))
		host_pcr_bit = PCR_ARCH_207;
	else if (cpu_has_feature(CPU_FTR_ARCH_206))
		host_pcr_bit = PCR_ARCH_206;
	else
		host_pcr_bit = PCR_ARCH_205;

	/* Determine lowest PCR bit needed to run guest in given PVR level */
	guest_pcr_bit = host_pcr_bit;
	if (arch_compat) {
		switch (arch_compat) {
		case PVR_ARCH_205:
			guest_pcr_bit = PCR_ARCH_205;
			break;
		case PVR_ARCH_206:
		case PVR_ARCH_206p:
			guest_pcr_bit = PCR_ARCH_206;
			break;
		case PVR_ARCH_207:
			guest_pcr_bit = PCR_ARCH_207;
			break;
		case PVR_ARCH_300:
			guest_pcr_bit = PCR_ARCH_300;
			break;
		default:
			return -EINVAL;
		}
	}

	/* Check requested PCR bits don't exceed our capabilities */
	if (guest_pcr_bit > host_pcr_bit)
		return -EINVAL;

	spin_lock(&vc->lock);
	vc->arch_compat = arch_compat;
	/*
	 * Set all PCR bits for which guest_pcr_bit <= bit < host_pcr_bit
	 * Also set all reserved PCR bits
	 */
	vc->pcr = (host_pcr_bit - guest_pcr_bit) | PCR_MASK;
	spin_unlock(&vc->lock);

	return 0;
}