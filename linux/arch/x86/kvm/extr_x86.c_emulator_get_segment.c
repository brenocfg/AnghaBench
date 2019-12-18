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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ctxt {int dummy; } ;
struct kvm_segment {int limit; int base; scalar_t__ g; int /*<<< orphan*/  db; int /*<<< orphan*/  l; int /*<<< orphan*/  avl; int /*<<< orphan*/  present; int /*<<< orphan*/  dpl; int /*<<< orphan*/  s; int /*<<< orphan*/  type; scalar_t__ unusable; int /*<<< orphan*/  selector; } ;
struct desc_struct {scalar_t__ g; int /*<<< orphan*/  d; int /*<<< orphan*/  l; int /*<<< orphan*/  avl; int /*<<< orphan*/  p; int /*<<< orphan*/  dpl; int /*<<< orphan*/  s; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  kvm_get_segment (int /*<<< orphan*/ ,struct kvm_segment*,int) ; 
 int /*<<< orphan*/  memset (struct desc_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_desc_base (struct desc_struct*,unsigned long) ; 
 int /*<<< orphan*/  set_desc_limit (struct desc_struct*,int) ; 

__attribute__((used)) static bool emulator_get_segment(struct x86_emulate_ctxt *ctxt, u16 *selector,
				 struct desc_struct *desc, u32 *base3,
				 int seg)
{
	struct kvm_segment var;

	kvm_get_segment(emul_to_vcpu(ctxt), &var, seg);
	*selector = var.selector;

	if (var.unusable) {
		memset(desc, 0, sizeof(*desc));
		if (base3)
			*base3 = 0;
		return false;
	}

	if (var.g)
		var.limit >>= 12;
	set_desc_limit(desc, var.limit);
	set_desc_base(desc, (unsigned long)var.base);
#ifdef CONFIG_X86_64
	if (base3)
		*base3 = var.base >> 32;
#endif
	desc->type = var.type;
	desc->s = var.s;
	desc->dpl = var.dpl;
	desc->p = var.present;
	desc->avl = var.avl;
	desc->l = var.l;
	desc->d = var.db;
	desc->g = var.g;

	return true;
}