#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmcs12 {int dummy; } ;
struct vmcs {int dummy; } ;
struct TYPE_4__ {struct vmcs* shadow_vmcs; } ;
struct vcpu_vmx {TYPE_1__* loaded_vmcs; int /*<<< orphan*/  vcpu; TYPE_2__ vmcs01; } ;
struct shadow_vmcs_field {int /*<<< orphan*/  offset; int /*<<< orphan*/  encoding; } ;
struct TYPE_3__ {struct vmcs* vmcs; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 unsigned long __vmcs_readl (int /*<<< orphan*/ ) ; 
 struct vmcs12* get_vmcs12 (int /*<<< orphan*/ *) ; 
 int max_shadow_read_write_fields ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct shadow_vmcs_field* shadow_read_write_fields ; 
 int /*<<< orphan*/  vmcs12_write_any (struct vmcs12*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmcs_clear (struct vmcs*) ; 
 int /*<<< orphan*/  vmcs_load (struct vmcs*) ; 

__attribute__((used)) static void copy_shadow_to_vmcs12(struct vcpu_vmx *vmx)
{
	struct vmcs *shadow_vmcs = vmx->vmcs01.shadow_vmcs;
	struct vmcs12 *vmcs12 = get_vmcs12(&vmx->vcpu);
	struct shadow_vmcs_field field;
	unsigned long val;
	int i;

	if (WARN_ON(!shadow_vmcs))
		return;

	preempt_disable();

	vmcs_load(shadow_vmcs);

	for (i = 0; i < max_shadow_read_write_fields; i++) {
		field = shadow_read_write_fields[i];
		val = __vmcs_readl(field.encoding);
		vmcs12_write_any(vmcs12, field.encoding, field.offset, val);
	}

	vmcs_clear(shadow_vmcs);
	vmcs_load(vmx->loaded_vmcs->vmcs);

	preempt_enable();
}