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
struct TYPE_2__ {int /*<<< orphan*/  wd_expired; } ;
struct ena_adapter {scalar_t__ wd_active; scalar_t__ keep_alive_timeout; int /*<<< orphan*/  reset_reason; TYPE_1__ dev_stats; int /*<<< orphan*/  pdev; int /*<<< orphan*/  keep_alive_timestamp; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 scalar_t__ ENA_HW_HINTS_NO_TIMEOUT ; 
 int /*<<< orphan*/  ENA_REGS_RESET_KEEP_ALIVE_TO ; 
 scalar_t__ atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ getsbinuptime () ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_for_missing_keep_alive(struct ena_adapter *adapter)
{
	sbintime_t timestamp, time;

	if (adapter->wd_active == 0)
		return;

	if (adapter->keep_alive_timeout == ENA_HW_HINTS_NO_TIMEOUT)
		return;

	timestamp = atomic_load_acq_64(&adapter->keep_alive_timestamp);
	time = getsbinuptime() - timestamp;
	if (unlikely(time > adapter->keep_alive_timeout)) {
		device_printf(adapter->pdev,
		    "Keep alive watchdog timeout.\n");
		counter_u64_add(adapter->dev_stats.wd_expired, 1);
		if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
			adapter->reset_reason = ENA_REGS_RESET_KEEP_ALIVE_TO;
			ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, adapter);
		}
	}
}