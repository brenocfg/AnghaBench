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
typedef  int u32 ;

/* Variables and functions */
#define  APIC_EOI 129 
#define  APIC_TASKPRI 128 
 int /*<<< orphan*/  HV_X64_MSR_EOI ; 
 int /*<<< orphan*/  HV_X64_MSR_TPR ; 
 int /*<<< orphan*/  native_apic_mem_write (int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_apic_write(u32 reg, u32 val)
{
	switch (reg) {
	case APIC_EOI:
		wrmsr(HV_X64_MSR_EOI, val, 0);
		break;
	case APIC_TASKPRI:
		wrmsr(HV_X64_MSR_TPR, val, 0);
		break;
	default:
		native_apic_mem_write(reg, val);
	}
}