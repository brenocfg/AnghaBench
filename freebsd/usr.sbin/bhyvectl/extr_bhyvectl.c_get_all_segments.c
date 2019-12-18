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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_IDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  VM_REG_GUEST_TR ; 
 int /*<<< orphan*/  desc_access ; 
 int /*<<< orphan*/  desc_base ; 
 int /*<<< orphan*/  desc_limit ; 
 scalar_t__ get_all ; 
 scalar_t__ get_cs ; 
 scalar_t__ get_desc_cs ; 
 scalar_t__ get_desc_ds ; 
 scalar_t__ get_desc_es ; 
 scalar_t__ get_desc_fs ; 
 scalar_t__ get_desc_gdtr ; 
 scalar_t__ get_desc_gs ; 
 scalar_t__ get_desc_idtr ; 
 scalar_t__ get_desc_ldtr ; 
 scalar_t__ get_desc_ss ; 
 scalar_t__ get_desc_tr ; 
 scalar_t__ get_ds ; 
 scalar_t__ get_es ; 
 scalar_t__ get_fs ; 
 scalar_t__ get_gs ; 
 scalar_t__ get_ldtr ; 
 scalar_t__ get_ss ; 
 scalar_t__ get_tr ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,...) ; 
 int vm_get_desc (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vm_get_register (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_all_segments(struct vmctx *ctx, int vcpu)
{
	uint64_t cs, ds, es, fs, gs, ss, tr, ldtr;
	int error = 0;

	if (!error && (get_desc_ds || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_DS,
				   &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("ds desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			      vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_es || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_ES,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("es desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_fs || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_FS,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("fs desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_gs || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_GS,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("gs desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_ss || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_SS,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("ss desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_cs || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_CS,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("cs desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_tr || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_TR,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("tr desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_ldtr || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_LDTR,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("ldtr desc[%d]\t0x%016lx/0x%08x/0x%08x\n",
			       vcpu, desc_base, desc_limit, desc_access);
		}
	}

	if (!error && (get_desc_gdtr || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_GDTR,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("gdtr[%d]\t\t0x%016lx/0x%08x\n",
			       vcpu, desc_base, desc_limit);
		}
	}

	if (!error && (get_desc_idtr || get_all)) {
		error = vm_get_desc(ctx, vcpu, VM_REG_GUEST_IDTR,
				    &desc_base, &desc_limit, &desc_access);
		if (error == 0) {
			printf("idtr[%d]\t\t0x%016lx/0x%08x\n",
			       vcpu, desc_base, desc_limit);
		}
	}

	if (!error && (get_cs || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_CS, &cs);
		if (error == 0)
			printf("cs[%d]\t\t0x%04lx\n", vcpu, cs);
	}

	if (!error && (get_ds || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DS, &ds);
		if (error == 0)
			printf("ds[%d]\t\t0x%04lx\n", vcpu, ds);
	}

	if (!error && (get_es || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_ES, &es);
		if (error == 0)
			printf("es[%d]\t\t0x%04lx\n", vcpu, es);
	}

	if (!error && (get_fs || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_FS, &fs);
		if (error == 0)
			printf("fs[%d]\t\t0x%04lx\n", vcpu, fs);
	}

	if (!error && (get_gs || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_GS, &gs);
		if (error == 0)
			printf("gs[%d]\t\t0x%04lx\n", vcpu, gs);
	}

	if (!error && (get_ss || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_SS, &ss);
		if (error == 0)
			printf("ss[%d]\t\t0x%04lx\n", vcpu, ss);
	}

	if (!error && (get_tr || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_TR, &tr);
		if (error == 0)
			printf("tr[%d]\t\t0x%04lx\n", vcpu, tr);
	}

	if (!error && (get_ldtr || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_LDTR, &ldtr);
		if (error == 0)
			printf("ldtr[%d]\t\t0x%04lx\n", vcpu, ldtr);
	}

	return (error);
}