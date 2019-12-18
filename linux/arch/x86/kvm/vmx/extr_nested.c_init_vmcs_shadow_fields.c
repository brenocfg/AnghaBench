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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct shadow_vmcs_field {int encoding; int offset; } ;

/* Variables and functions */
 int GUEST_ES_AR_BYTES ; 
#define  GUEST_INTR_STATUS 130 
#define  GUEST_PML_INDEX 129 
 int GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ VMCS_FIELD_WIDTH_U64 ; 
#define  VMX_PREEMPTION_TIMER_VALUE 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_vmx_apicv () ; 
 int /*<<< orphan*/  cpu_has_vmx_pml () ; 
 int /*<<< orphan*/  cpu_has_vmx_preemption_timer () ; 
 int max_shadow_read_only_fields ; 
 int max_shadow_read_write_fields ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct shadow_vmcs_field* shadow_read_only_fields ; 
 struct shadow_vmcs_field* shadow_read_write_fields ; 
 scalar_t__ vmcs_field_width (int) ; 
 int /*<<< orphan*/  vmx_vmread_bitmap ; 
 int /*<<< orphan*/  vmx_vmwrite_bitmap ; 

__attribute__((used)) static void init_vmcs_shadow_fields(void)
{
	int i, j;

	memset(vmx_vmread_bitmap, 0xff, PAGE_SIZE);
	memset(vmx_vmwrite_bitmap, 0xff, PAGE_SIZE);

	for (i = j = 0; i < max_shadow_read_only_fields; i++) {
		struct shadow_vmcs_field entry = shadow_read_only_fields[i];
		u16 field = entry.encoding;

		if (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shadow_read_only_fields ||
		     shadow_read_only_fields[i + 1].encoding != field + 1))
			pr_err("Missing field from shadow_read_only_field %x\n",
			       field + 1);

		clear_bit(field, vmx_vmread_bitmap);
		if (field & 1)
#ifdef CONFIG_X86_64
			continue;
#else
			entry.offset += sizeof(u32);
#endif
		shadow_read_only_fields[j++] = entry;
	}
	max_shadow_read_only_fields = j;

	for (i = j = 0; i < max_shadow_read_write_fields; i++) {
		struct shadow_vmcs_field entry = shadow_read_write_fields[i];
		u16 field = entry.encoding;

		if (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shadow_read_write_fields ||
		     shadow_read_write_fields[i + 1].encoding != field + 1))
			pr_err("Missing field from shadow_read_write_field %x\n",
			       field + 1);

		WARN_ONCE(field >= GUEST_ES_AR_BYTES &&
			  field <= GUEST_TR_AR_BYTES,
			  "Update vmcs12_write_any() to drop reserved bits from AR_BYTES");

		/*
		 * PML and the preemption timer can be emulated, but the
		 * processor cannot vmwrite to fields that don't exist
		 * on bare metal.
		 */
		switch (field) {
		case GUEST_PML_INDEX:
			if (!cpu_has_vmx_pml())
				continue;
			break;
		case VMX_PREEMPTION_TIMER_VALUE:
			if (!cpu_has_vmx_preemption_timer())
				continue;
			break;
		case GUEST_INTR_STATUS:
			if (!cpu_has_vmx_apicv())
				continue;
			break;
		default:
			break;
		}

		clear_bit(field, vmx_vmwrite_bitmap);
		clear_bit(field, vmx_vmread_bitmap);
		if (field & 1)
#ifdef CONFIG_X86_64
			continue;
#else
			entry.offset += sizeof(u32);
#endif
		shadow_read_write_fields[j++] = entry;
	}
	max_shadow_read_write_fields = j;
}