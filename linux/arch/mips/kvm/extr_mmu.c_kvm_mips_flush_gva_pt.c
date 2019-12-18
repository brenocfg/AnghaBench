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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  enum kvm_mips_flush { ____Placeholder_kvm_mips_flush } kvm_mips_flush ;

/* Variables and functions */
 int KMF_GPA ; 
 int KMF_KERN ; 
 int /*<<< orphan*/  kvm_mips_flush_gva_pgd (int /*<<< orphan*/ *,int,int) ; 

void kvm_mips_flush_gva_pt(pgd_t *pgd, enum kvm_mips_flush flags)
{
	if (flags & KMF_GPA) {
		/* all of guest virtual address space could be affected */
		if (flags & KMF_KERN)
			/* useg, kseg0, seg2/3 */
			kvm_mips_flush_gva_pgd(pgd, 0, 0x7fffffff);
		else
			/* useg */
			kvm_mips_flush_gva_pgd(pgd, 0, 0x3fffffff);
	} else {
		/* useg */
		kvm_mips_flush_gva_pgd(pgd, 0, 0x3fffffff);

		/* kseg2/3 */
		if (flags & KMF_KERN)
			kvm_mips_flush_gva_pgd(pgd, 0x60000000, 0x7fffffff);
	}
}