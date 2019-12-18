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
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {TYPE_1__ dest_map; scalar_t__ pending_eoi; } ;
struct kvm_ioapic {TYPE_2__ rtc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MAX_VCPU_ID ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc_irq_eoi_tracking_reset(struct kvm_ioapic *ioapic)
{
	ioapic->rtc_status.pending_eoi = 0;
	bitmap_zero(ioapic->rtc_status.dest_map.map, KVM_MAX_VCPU_ID);
}