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
struct TYPE_2__ {int /*<<< orphan*/  (* SetTimer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* CreateEvent ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int EVT_NOTIFY_SIGNAL ; 
 int EVT_TIMER ; 
 int /*<<< orphan*/  TPL_CALLBACK ; 
 int /*<<< orphan*/  TimerPeriodic ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_event ; 
 int /*<<< orphan*/  time_update ; 

void
efi_time_init(void)
{

	/* Create a timer event */
	BS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
	    time_update, 0, &time_event);
	/* Use a 10ms timer */
	BS->SetTimer(time_event, TimerPeriodic, 100000);
}