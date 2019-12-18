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
struct TYPE_3__ {struct vmcs* shadow_vmcs; } ;
struct vcpu_vmx {TYPE_2__* loaded_vmcs; int /*<<< orphan*/  vcpu; TYPE_1__ vmcs01; } ;
struct shadow_vmcs_field {int /*<<< orphan*/  encoding; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {struct vmcs* vmcs; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct shadow_vmcs_field const**) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 
 struct vmcs12* get_vmcs12 (int /*<<< orphan*/ *) ; 
 int const max_shadow_read_only_fields ; 
 int const max_shadow_read_write_fields ; 
 struct shadow_vmcs_field const* shadow_read_only_fields ; 
 struct shadow_vmcs_field const* shadow_read_write_fields ; 
 unsigned long vmcs12_read_any (struct vmcs12*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_clear (struct vmcs*) ; 
 int /*<<< orphan*/  vmcs_load (struct vmcs*) ; 

__attribute__((used)) static void copy_vmcs12_to_shadow(struct vcpu_vmx *vmx)
{
	const struct shadow_vmcs_field *fields[] = {
		shadow_read_write_fields,
		shadow_read_only_fields
	};
	const int max_fields[] = {
		max_shadow_read_write_fields,
		max_shadow_read_only_fields
	};
	struct vmcs *shadow_vmcs = vmx->vmcs01.shadow_vmcs;
	struct vmcs12 *vmcs12 = get_vmcs12(&vmx->vcpu);
	struct shadow_vmcs_field field;
	unsigned long val;
	int i, q;

	if (WARN_ON(!shadow_vmcs))
		return;

	vmcs_load(shadow_vmcs);

	for (q = 0; q < ARRAY_SIZE(fields); q++) {
		for (i = 0; i < max_fields[q]; i++) {
			field = fields[q][i];
			val = vmcs12_read_any(vmcs12, field.encoding,
					      field.offset);
			__vmcs_writel(field.encoding, val);
		}
	}

	vmcs_clear(shadow_vmcs);
	vmcs_load(vmx->loaded_vmcs->vmcs);
}