#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
typedef  int /*<<< orphan*/  efi_time_t ;
typedef  int /*<<< orphan*/  efi_time_cap_t ;
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
typedef  int /*<<< orphan*/  efi_capsule_header_t ;
typedef  int /*<<< orphan*/  efi_bool_t ;
struct TYPE_2__ {int efi_rts_id; int /*<<< orphan*/  efi_rts_comp; int /*<<< orphan*/  status; void* arg5; void* arg4; void* arg3; void* arg2; void* arg1; } ;

/* Variables and functions */
#define  EFI_GET_NEXT_HIGH_MONO_COUNT 138 
#define  EFI_GET_NEXT_VARIABLE 137 
#define  EFI_GET_TIME 136 
#define  EFI_GET_VARIABLE 135 
#define  EFI_GET_WAKEUP_TIME 134 
 int /*<<< orphan*/  EFI_NOT_FOUND ; 
#define  EFI_QUERY_CAPSULE_CAPS 133 
#define  EFI_QUERY_VARIABLE_INFO 132 
#define  EFI_SET_TIME 131 
#define  EFI_SET_VARIABLE 130 
#define  EFI_SET_WAKEUP_TIME 129 
#define  EFI_UPDATE_CAPSULE 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_call_virt (int /*<<< orphan*/ ,unsigned long*,...) ; 
 TYPE_1__ efi_rts_work ; 
 int /*<<< orphan*/  get_next_high_mono_count ; 
 int /*<<< orphan*/  get_next_variable ; 
 int /*<<< orphan*/  get_time ; 
 int /*<<< orphan*/  get_variable ; 
 int /*<<< orphan*/  get_wakeup_time ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  query_capsule_caps ; 
 int /*<<< orphan*/  query_variable_info ; 
 int /*<<< orphan*/  set_time ; 
 int /*<<< orphan*/  set_variable ; 
 int /*<<< orphan*/  set_wakeup_time ; 
 int /*<<< orphan*/  update_capsule ; 

__attribute__((used)) static void efi_call_rts(struct work_struct *work)
{
	void *arg1, *arg2, *arg3, *arg4, *arg5;
	efi_status_t status = EFI_NOT_FOUND;

	arg1 = efi_rts_work.arg1;
	arg2 = efi_rts_work.arg2;
	arg3 = efi_rts_work.arg3;
	arg4 = efi_rts_work.arg4;
	arg5 = efi_rts_work.arg5;

	switch (efi_rts_work.efi_rts_id) {
	case EFI_GET_TIME:
		status = efi_call_virt(get_time, (efi_time_t *)arg1,
				       (efi_time_cap_t *)arg2);
		break;
	case EFI_SET_TIME:
		status = efi_call_virt(set_time, (efi_time_t *)arg1);
		break;
	case EFI_GET_WAKEUP_TIME:
		status = efi_call_virt(get_wakeup_time, (efi_bool_t *)arg1,
				       (efi_bool_t *)arg2, (efi_time_t *)arg3);
		break;
	case EFI_SET_WAKEUP_TIME:
		status = efi_call_virt(set_wakeup_time, *(efi_bool_t *)arg1,
				       (efi_time_t *)arg2);
		break;
	case EFI_GET_VARIABLE:
		status = efi_call_virt(get_variable, (efi_char16_t *)arg1,
				       (efi_guid_t *)arg2, (u32 *)arg3,
				       (unsigned long *)arg4, (void *)arg5);
		break;
	case EFI_GET_NEXT_VARIABLE:
		status = efi_call_virt(get_next_variable, (unsigned long *)arg1,
				       (efi_char16_t *)arg2,
				       (efi_guid_t *)arg3);
		break;
	case EFI_SET_VARIABLE:
		status = efi_call_virt(set_variable, (efi_char16_t *)arg1,
				       (efi_guid_t *)arg2, *(u32 *)arg3,
				       *(unsigned long *)arg4, (void *)arg5);
		break;
	case EFI_QUERY_VARIABLE_INFO:
		status = efi_call_virt(query_variable_info, *(u32 *)arg1,
				       (u64 *)arg2, (u64 *)arg3, (u64 *)arg4);
		break;
	case EFI_GET_NEXT_HIGH_MONO_COUNT:
		status = efi_call_virt(get_next_high_mono_count, (u32 *)arg1);
		break;
	case EFI_UPDATE_CAPSULE:
		status = efi_call_virt(update_capsule,
				       (efi_capsule_header_t **)arg1,
				       *(unsigned long *)arg2,
				       *(unsigned long *)arg3);
		break;
	case EFI_QUERY_CAPSULE_CAPS:
		status = efi_call_virt(query_capsule_caps,
				       (efi_capsule_header_t **)arg1,
				       *(unsigned long *)arg2, (u64 *)arg3,
				       (int *)arg4);
		break;
	default:
		/*
		 * Ideally, we should never reach here because a caller of this
		 * function should have put the right efi_runtime_service()
		 * function identifier into efi_rts_work->efi_rts_id
		 */
		pr_err("Requested executing invalid EFI Runtime Service.\n");
	}
	efi_rts_work.status = status;
	complete(&efi_rts_work.efi_rts_comp);
}