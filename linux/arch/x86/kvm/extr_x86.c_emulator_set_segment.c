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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ctxt {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int base; int limit; int unusable; scalar_t__ padding; int /*<<< orphan*/  present; int /*<<< orphan*/  avl; scalar_t__ g; int /*<<< orphan*/  l; int /*<<< orphan*/  s; int /*<<< orphan*/  db; int /*<<< orphan*/  dpl; int /*<<< orphan*/  type; int /*<<< orphan*/  selector; } ;
struct desc_struct {int /*<<< orphan*/  p; int /*<<< orphan*/  avl; scalar_t__ g; int /*<<< orphan*/  l; int /*<<< orphan*/  s; int /*<<< orphan*/  d; int /*<<< orphan*/  dpl; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int get_desc_base (struct desc_struct*) ; 
 int get_desc_limit (struct desc_struct*) ; 
 int /*<<< orphan*/  kvm_set_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 

__attribute__((used)) static void emulator_set_segment(struct x86_emulate_ctxt *ctxt, u16 selector,
				 struct desc_struct *desc, u32 base3,
				 int seg)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	struct kvm_segment var;

	var.selector = selector;
	var.base = get_desc_base(desc);
#ifdef CONFIG_X86_64
	var.base |= ((u64)base3) << 32;
#endif
	var.limit = get_desc_limit(desc);
	if (desc->g)
		var.limit = (var.limit << 12) | 0xfff;
	var.type = desc->type;
	var.dpl = desc->dpl;
	var.db = desc->d;
	var.s = desc->s;
	var.l = desc->l;
	var.g = desc->g;
	var.avl = desc->avl;
	var.present = desc->p;
	var.unusable = !var.present;
	var.padding = 0;

	kvm_set_segment(vcpu, &var, seg);
	return;
}