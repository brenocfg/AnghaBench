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
struct TYPE_2__ {int /*<<< orphan*/  query_capsule_caps; int /*<<< orphan*/  update_capsule; int /*<<< orphan*/  query_variable_info_nonblocking; int /*<<< orphan*/  query_variable_info; int /*<<< orphan*/  reset_system; int /*<<< orphan*/  get_next_high_mono_count; int /*<<< orphan*/  set_variable_nonblocking; int /*<<< orphan*/  set_variable; int /*<<< orphan*/  get_next_variable; int /*<<< orphan*/  get_variable; int /*<<< orphan*/  set_wakeup_time; int /*<<< orphan*/  get_wakeup_time; int /*<<< orphan*/  set_time; int /*<<< orphan*/  get_time; } ;

/* Variables and functions */
 TYPE_1__ efi ; 
 int /*<<< orphan*/  virt_efi_get_next_high_mono_count ; 
 int /*<<< orphan*/  virt_efi_get_next_variable ; 
 int /*<<< orphan*/  virt_efi_get_time ; 
 int /*<<< orphan*/  virt_efi_get_variable ; 
 int /*<<< orphan*/  virt_efi_get_wakeup_time ; 
 int /*<<< orphan*/  virt_efi_query_capsule_caps ; 
 int /*<<< orphan*/  virt_efi_query_variable_info ; 
 int /*<<< orphan*/  virt_efi_query_variable_info_nonblocking ; 
 int /*<<< orphan*/  virt_efi_reset_system ; 
 int /*<<< orphan*/  virt_efi_set_time ; 
 int /*<<< orphan*/  virt_efi_set_variable ; 
 int /*<<< orphan*/  virt_efi_set_variable_nonblocking ; 
 int /*<<< orphan*/  virt_efi_set_wakeup_time ; 
 int /*<<< orphan*/  virt_efi_update_capsule ; 

void efi_native_runtime_setup(void)
{
	efi.get_time = virt_efi_get_time;
	efi.set_time = virt_efi_set_time;
	efi.get_wakeup_time = virt_efi_get_wakeup_time;
	efi.set_wakeup_time = virt_efi_set_wakeup_time;
	efi.get_variable = virt_efi_get_variable;
	efi.get_next_variable = virt_efi_get_next_variable;
	efi.set_variable = virt_efi_set_variable;
	efi.set_variable_nonblocking = virt_efi_set_variable_nonblocking;
	efi.get_next_high_mono_count = virt_efi_get_next_high_mono_count;
	efi.reset_system = virt_efi_reset_system;
	efi.query_variable_info = virt_efi_query_variable_info;
	efi.query_variable_info_nonblocking = virt_efi_query_variable_info_nonblocking;
	efi.update_capsule = virt_efi_update_capsule;
	efi.query_capsule_caps = virt_efi_query_capsule_caps;
}