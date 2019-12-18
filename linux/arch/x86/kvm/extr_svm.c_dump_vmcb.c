#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_20__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_19__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_18__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_17__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_16__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_15__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_14__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_13__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct TYPE_12__ {int /*<<< orphan*/  base; int /*<<< orphan*/  limit; int /*<<< orphan*/  attrib; int /*<<< orphan*/  selector; } ;
struct vmcb_save_area {int /*<<< orphan*/  last_excp_to; int /*<<< orphan*/  last_excp_from; int /*<<< orphan*/  br_to; int /*<<< orphan*/  br_from; int /*<<< orphan*/  dbgctl; int /*<<< orphan*/  g_pat; int /*<<< orphan*/  sysenter_eip; int /*<<< orphan*/  sysenter_esp; int /*<<< orphan*/  sysenter_cs; int /*<<< orphan*/  kernel_gs_base; int /*<<< orphan*/  sfmask; int /*<<< orphan*/  cstar; int /*<<< orphan*/  lstar; int /*<<< orphan*/  star; int /*<<< orphan*/  rax; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/  cr4; int /*<<< orphan*/  cr3; int /*<<< orphan*/  cr2; int /*<<< orphan*/  cr0; int /*<<< orphan*/  efer; int /*<<< orphan*/  cpl; TYPE_8__ tr; TYPE_7__ idtr; TYPE_6__ ldtr; TYPE_5__ gdtr; TYPE_4__ gs; TYPE_3__ fs; TYPE_2__ ds; TYPE_1__ ss; TYPE_11__ cs; TYPE_10__ es; } ;
struct vmcb_control_area {int intercept_cr; int intercept_dr; int /*<<< orphan*/  avic_physical_id; int /*<<< orphan*/  avic_logical_id; int /*<<< orphan*/  avic_backing_page; int /*<<< orphan*/  next_rip; int /*<<< orphan*/  virt_ext; int /*<<< orphan*/  event_inj_err; int /*<<< orphan*/  event_inj; int /*<<< orphan*/  avic_vapic_bar; int /*<<< orphan*/  nested_cr3; int /*<<< orphan*/  nested_ctl; int /*<<< orphan*/  exit_int_info_err; int /*<<< orphan*/  exit_int_info; int /*<<< orphan*/  exit_info_2; int /*<<< orphan*/  exit_info_1; int /*<<< orphan*/  exit_code; int /*<<< orphan*/  int_state; int /*<<< orphan*/  int_vector; int /*<<< orphan*/  int_ctl; int /*<<< orphan*/  tlb_ctl; int /*<<< orphan*/  asid; int /*<<< orphan*/  tsc_offset; int /*<<< orphan*/  msrpm_base_pa; int /*<<< orphan*/  iopm_base_pa; int /*<<< orphan*/  pause_filter_thresh; int /*<<< orphan*/  pause_filter_count; int /*<<< orphan*/  intercept; int /*<<< orphan*/  intercept_exceptions; } ;
struct vcpu_svm {TYPE_9__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_22__ {struct vmcb_save_area save; struct vmcb_control_area control; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_invalid_vmcb ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void dump_vmcb(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct vmcb_control_area *control = &svm->vmcb->control;
	struct vmcb_save_area *save = &svm->vmcb->save;

	if (!dump_invalid_vmcb) {
		pr_warn_ratelimited("set kvm_amd.dump_invalid_vmcb=1 to dump internal KVM state.\n");
		return;
	}

	pr_err("VMCB Control Area:\n");
	pr_err("%-20s%04x\n", "cr_read:", control->intercept_cr & 0xffff);
	pr_err("%-20s%04x\n", "cr_write:", control->intercept_cr >> 16);
	pr_err("%-20s%04x\n", "dr_read:", control->intercept_dr & 0xffff);
	pr_err("%-20s%04x\n", "dr_write:", control->intercept_dr >> 16);
	pr_err("%-20s%08x\n", "exceptions:", control->intercept_exceptions);
	pr_err("%-20s%016llx\n", "intercepts:", control->intercept);
	pr_err("%-20s%d\n", "pause filter count:", control->pause_filter_count);
	pr_err("%-20s%d\n", "pause filter threshold:",
	       control->pause_filter_thresh);
	pr_err("%-20s%016llx\n", "iopm_base_pa:", control->iopm_base_pa);
	pr_err("%-20s%016llx\n", "msrpm_base_pa:", control->msrpm_base_pa);
	pr_err("%-20s%016llx\n", "tsc_offset:", control->tsc_offset);
	pr_err("%-20s%d\n", "asid:", control->asid);
	pr_err("%-20s%d\n", "tlb_ctl:", control->tlb_ctl);
	pr_err("%-20s%08x\n", "int_ctl:", control->int_ctl);
	pr_err("%-20s%08x\n", "int_vector:", control->int_vector);
	pr_err("%-20s%08x\n", "int_state:", control->int_state);
	pr_err("%-20s%08x\n", "exit_code:", control->exit_code);
	pr_err("%-20s%016llx\n", "exit_info1:", control->exit_info_1);
	pr_err("%-20s%016llx\n", "exit_info2:", control->exit_info_2);
	pr_err("%-20s%08x\n", "exit_int_info:", control->exit_int_info);
	pr_err("%-20s%08x\n", "exit_int_info_err:", control->exit_int_info_err);
	pr_err("%-20s%lld\n", "nested_ctl:", control->nested_ctl);
	pr_err("%-20s%016llx\n", "nested_cr3:", control->nested_cr3);
	pr_err("%-20s%016llx\n", "avic_vapic_bar:", control->avic_vapic_bar);
	pr_err("%-20s%08x\n", "event_inj:", control->event_inj);
	pr_err("%-20s%08x\n", "event_inj_err:", control->event_inj_err);
	pr_err("%-20s%lld\n", "virt_ext:", control->virt_ext);
	pr_err("%-20s%016llx\n", "next_rip:", control->next_rip);
	pr_err("%-20s%016llx\n", "avic_backing_page:", control->avic_backing_page);
	pr_err("%-20s%016llx\n", "avic_logical_id:", control->avic_logical_id);
	pr_err("%-20s%016llx\n", "avic_physical_id:", control->avic_physical_id);
	pr_err("VMCB State Save Area:\n");
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "es:",
	       save->es.selector, save->es.attrib,
	       save->es.limit, save->es.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "cs:",
	       save->cs.selector, save->cs.attrib,
	       save->cs.limit, save->cs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ss:",
	       save->ss.selector, save->ss.attrib,
	       save->ss.limit, save->ss.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ds:",
	       save->ds.selector, save->ds.attrib,
	       save->ds.limit, save->ds.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "fs:",
	       save->fs.selector, save->fs.attrib,
	       save->fs.limit, save->fs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "gs:",
	       save->gs.selector, save->gs.attrib,
	       save->gs.limit, save->gs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "gdtr:",
	       save->gdtr.selector, save->gdtr.attrib,
	       save->gdtr.limit, save->gdtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ldtr:",
	       save->ldtr.selector, save->ldtr.attrib,
	       save->ldtr.limit, save->ldtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "idtr:",
	       save->idtr.selector, save->idtr.attrib,
	       save->idtr.limit, save->idtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "tr:",
	       save->tr.selector, save->tr.attrib,
	       save->tr.limit, save->tr.base);
	pr_err("cpl:            %d                efer:         %016llx\n",
		save->cpl, save->efer);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cr0:", save->cr0, "cr2:", save->cr2);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cr3:", save->cr3, "cr4:", save->cr4);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "dr6:", save->dr6, "dr7:", save->dr7);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "rip:", save->rip, "rflags:", save->rflags);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "rsp:", save->rsp, "rax:", save->rax);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "star:", save->star, "lstar:", save->lstar);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cstar:", save->cstar, "sfmask:", save->sfmask);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "kernel_gs_base:", save->kernel_gs_base,
	       "sysenter_cs:", save->sysenter_cs);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "sysenter_esp:", save->sysenter_esp,
	       "sysenter_eip:", save->sysenter_eip);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "gpat:", save->g_pat, "dbgctl:", save->dbgctl);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "br_from:", save->br_from, "br_to:", save->br_to);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "excp_from:", save->last_excp_from,
	       "excp_to:", save->last_excp_to);
}