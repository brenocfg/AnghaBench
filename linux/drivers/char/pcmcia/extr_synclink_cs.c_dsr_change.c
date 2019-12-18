#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dsr_down; int /*<<< orphan*/  dsr_up; } ;
struct TYPE_7__ {int /*<<< orphan*/  dsr; } ;
struct TYPE_9__ {int serial_signals; int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_2__ input_signal_events; TYPE_1__ icount; int /*<<< orphan*/  dsr_chkcount; } ;
typedef  TYPE_3__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_STATUS ; 
 scalar_t__ IO_PIN_SHUTDOWN_LIMIT ; 
 int /*<<< orphan*/  PVR_DSR ; 
 int SerialSignal_DSR ; 
 int /*<<< orphan*/  get_signals (TYPE_3__*) ; 
 int /*<<< orphan*/  port_irq_disable (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsr_change(MGSLPC_INFO *info)
{
	get_signals(info);
	if ((info->dsr_chkcount)++ >= IO_PIN_SHUTDOWN_LIMIT)
		port_irq_disable(info, PVR_DSR);
	info->icount.dsr++;
	if (info->serial_signals & SerialSignal_DSR)
		info->input_signal_events.dsr_up++;
	else
		info->input_signal_events.dsr_down++;
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;
}