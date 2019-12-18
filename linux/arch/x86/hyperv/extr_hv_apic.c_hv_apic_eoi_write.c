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
struct hv_vp_assist_page {int /*<<< orphan*/  apic_assist; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_EOI ; 
 struct hv_vp_assist_page** hv_vp_assist_page ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_apic_eoi_write(u32 reg, u32 val)
{
	struct hv_vp_assist_page *hvp = hv_vp_assist_page[smp_processor_id()];

	if (hvp && (xchg(&hvp->apic_assist, 0) & 0x1))
		return;

	wrmsr(HV_X64_MSR_EOI, val, 0);
}