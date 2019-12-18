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
struct TYPE_2__ {scalar_t__ pending_eoi; } ;
struct kvm_ioapic {TYPE_1__ rtc_status; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_rtc_eoi_tracking_restore_all (struct kvm_ioapic*) ; 

__attribute__((used)) static void rtc_status_pending_eoi_check_valid(struct kvm_ioapic *ioapic)
{
	if (WARN_ON(ioapic->rtc_status.pending_eoi < 0))
		kvm_rtc_eoi_tracking_restore_all(ioapic);
}