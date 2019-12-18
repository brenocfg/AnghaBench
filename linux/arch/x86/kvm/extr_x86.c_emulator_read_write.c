#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct x86_exception {int dummy; } ;
struct x86_emulate_ctxt {scalar_t__ mode; } ;
struct read_write_emulator_ops {int (* read_write_exit_mmio ) (struct kvm_vcpu*,int /*<<< orphan*/ ,void*,unsigned int) ;int /*<<< orphan*/  write; scalar_t__ (* read_write_prepare ) (struct kvm_vcpu*,void*,unsigned int) ;} ;
struct kvm_vcpu {int mmio_needed; TYPE_3__* run; int /*<<< orphan*/  mmio_is_write; TYPE_1__* mmio_fragments; scalar_t__ mmio_cur_fragment; scalar_t__ mmio_nr_fragments; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_5__ {int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  is_write; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {TYPE_2__ mmio; int /*<<< orphan*/  exit_reason; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  gpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_MMIO ; 
 unsigned long PAGE_MASK ; 
 int X86EMUL_CONTINUE ; 
 scalar_t__ X86EMUL_MODE_PROT64 ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int emulator_read_write_onepage (unsigned long,void*,unsigned int,struct x86_exception*,struct kvm_vcpu*,struct read_write_emulator_ops const*) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct kvm_vcpu*,void*,unsigned int) ; 
 int stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int emulator_read_write(struct x86_emulate_ctxt *ctxt,
			unsigned long addr,
			void *val, unsigned int bytes,
			struct x86_exception *exception,
			const struct read_write_emulator_ops *ops)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	gpa_t gpa;
	int rc;

	if (ops->read_write_prepare &&
		  ops->read_write_prepare(vcpu, val, bytes))
		return X86EMUL_CONTINUE;

	vcpu->mmio_nr_fragments = 0;

	/* Crossing a page boundary? */
	if (((addr + bytes - 1) ^ addr) & PAGE_MASK) {
		int now;

		now = -addr & ~PAGE_MASK;
		rc = emulator_read_write_onepage(addr, val, now, exception,
						 vcpu, ops);

		if (rc != X86EMUL_CONTINUE)
			return rc;
		addr += now;
		if (ctxt->mode != X86EMUL_MODE_PROT64)
			addr = (u32)addr;
		val += now;
		bytes -= now;
	}

	rc = emulator_read_write_onepage(addr, val, bytes, exception,
					 vcpu, ops);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	if (!vcpu->mmio_nr_fragments)
		return rc;

	gpa = vcpu->mmio_fragments[0].gpa;

	vcpu->mmio_needed = 1;
	vcpu->mmio_cur_fragment = 0;

	vcpu->run->mmio.len = min(8u, vcpu->mmio_fragments[0].len);
	vcpu->run->mmio.is_write = vcpu->mmio_is_write = ops->write;
	vcpu->run->exit_reason = KVM_EXIT_MMIO;
	vcpu->run->mmio.phys_addr = gpa;

	return ops->read_write_exit_mmio(vcpu, gpa, val, bytes);
}