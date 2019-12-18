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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int kvm_mips_mkold_gpa_pt (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_age_hva_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end,
			       struct kvm_memory_slot *memslot, void *data)
{
	return kvm_mips_mkold_gpa_pt(kvm, gfn, gfn_end);
}