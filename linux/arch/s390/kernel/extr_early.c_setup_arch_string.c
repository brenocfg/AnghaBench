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
struct sysinfo_3_2_2 {char* manufacturer; char* type; char* model; char* model_capacity; TYPE_1__* vm; scalar_t__ count; } ;
struct sysinfo_1_1_1 {char* manufacturer; char* type; char* model; char* model_capacity; TYPE_1__* vm; scalar_t__ count; } ;
struct TYPE_2__ {char* cpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,int) ; 
 scalar_t__ MACHINE_IS_KVM ; 
 scalar_t__ MACHINE_IS_LPAR ; 
 scalar_t__ MACHINE_IS_VM ; 
 int /*<<< orphan*/  dump_stack_set_arch_desc (char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strim_all (char*) ; 
 scalar_t__ stsi (struct sysinfo_3_2_2*,int,int,int) ; 
 int /*<<< orphan*/  sysinfo_page ; 

void setup_arch_string(void)
{
	struct sysinfo_1_1_1 *mach = (struct sysinfo_1_1_1 *)&sysinfo_page;
	struct sysinfo_3_2_2 *vm = (struct sysinfo_3_2_2 *)&sysinfo_page;
	char mstr[80], hvstr[17];

	if (stsi(mach, 1, 1, 1))
		return;
	EBCASC(mach->manufacturer, sizeof(mach->manufacturer));
	EBCASC(mach->type, sizeof(mach->type));
	EBCASC(mach->model, sizeof(mach->model));
	EBCASC(mach->model_capacity, sizeof(mach->model_capacity));
	sprintf(mstr, "%-16.16s %-4.4s %-16.16s %-16.16s",
		mach->manufacturer, mach->type,
		mach->model, mach->model_capacity);
	strim_all(mstr);
	if (stsi(vm, 3, 2, 2) == 0 && vm->count) {
		EBCASC(vm->vm[0].cpi, sizeof(vm->vm[0].cpi));
		sprintf(hvstr, "%-16.16s", vm->vm[0].cpi);
		strim_all(hvstr);
	} else {
		sprintf(hvstr, "%s",
			MACHINE_IS_LPAR ? "LPAR" :
			MACHINE_IS_VM ? "z/VM" :
			MACHINE_IS_KVM ? "KVM" : "unknown");
	}
	dump_stack_set_arch_desc("%s (%s)", mstr, hvstr);
}