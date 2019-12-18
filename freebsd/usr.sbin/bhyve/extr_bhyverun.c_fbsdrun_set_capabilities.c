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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int BSP ; 
 int /*<<< orphan*/  VM_CAP_ENABLE_INVPCID ; 
 int /*<<< orphan*/  VM_CAP_HALT_EXIT ; 
 int /*<<< orphan*/  VM_CAP_PAUSE_EXIT ; 
 size_t VM_EXITCODE_HLT ; 
 size_t VM_EXITCODE_PAUSE ; 
 int /*<<< orphan*/  X2APIC_DISABLED ; 
 int /*<<< orphan*/  X2APIC_ENABLED ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fbsdrun_vmexit_on_hlt () ; 
 scalar_t__ fbsdrun_vmexit_on_pause () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * handler ; 
 int /*<<< orphan*/  stderr ; 
 int vm_get_capability (struct vmctx*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_set_capability (struct vmctx*,int,int /*<<< orphan*/ ,int) ; 
 int vm_set_x2apic_state (struct vmctx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmexit_hlt ; 
 int /*<<< orphan*/  vmexit_pause ; 
 scalar_t__ x2apic_mode ; 

void
fbsdrun_set_capabilities(struct vmctx *ctx, int cpu)
{
	int err, tmp;

	if (fbsdrun_vmexit_on_hlt()) {
		err = vm_get_capability(ctx, cpu, VM_CAP_HALT_EXIT, &tmp);
		if (err < 0) {
			fprintf(stderr, "VM exit on HLT not supported\n");
			exit(4);
		}
		vm_set_capability(ctx, cpu, VM_CAP_HALT_EXIT, 1);
		if (cpu == BSP)
			handler[VM_EXITCODE_HLT] = vmexit_hlt;
	}

        if (fbsdrun_vmexit_on_pause()) {
		/*
		 * pause exit support required for this mode
		 */
		err = vm_get_capability(ctx, cpu, VM_CAP_PAUSE_EXIT, &tmp);
		if (err < 0) {
			fprintf(stderr,
			    "SMP mux requested, no pause support\n");
			exit(4);
		}
		vm_set_capability(ctx, cpu, VM_CAP_PAUSE_EXIT, 1);
		if (cpu == BSP)
			handler[VM_EXITCODE_PAUSE] = vmexit_pause;
        }

	if (x2apic_mode)
		err = vm_set_x2apic_state(ctx, cpu, X2APIC_ENABLED);
	else
		err = vm_set_x2apic_state(ctx, cpu, X2APIC_DISABLED);

	if (err) {
		fprintf(stderr, "Unable to set x2apic state (%d)\n", err);
		exit(4);
	}

	vm_set_capability(ctx, cpu, VM_CAP_ENABLE_INVPCID, 1);
}