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
typedef  int ulong ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ESID_MASK ; 
 int /*<<< orphan*/  dprintk_mmu (char*,int,int,int,int) ; 
 int htab ; 
 int htabmask ; 

__attribute__((used)) static u32 *kvmppc_mmu_get_pteg(struct kvm_vcpu *vcpu, u32 vsid, u32 eaddr,
				bool primary)
{
	u32 page, hash;
	ulong pteg = htab;

	page = (eaddr & ~ESID_MASK) >> 12;

	hash = ((vsid ^ page) << 6);
	if (!primary)
		hash = ~hash;

	hash &= htabmask;

	pteg |= hash;

	dprintk_mmu("htab: %lx | hash: %x | htabmask: %x | pteg: %lx\n",
		htab, hash, htabmask, pteg);

	return (u32*)pteg;
}