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
typedef  int uint32_t ;
struct ISCI_TIMER {int /*<<< orphan*/  callout; int /*<<< orphan*/  is_started; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int SBT_1MS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_log_message (int,char*,char*,void*,int) ; 
 int /*<<< orphan*/  isci_timer_timeout ; 

void
scif_cb_timer_start(SCI_CONTROLLER_HANDLE_T controller, void *timer,
    uint32_t milliseconds)
{
	struct ISCI_TIMER *isci_timer = (struct ISCI_TIMER *)timer;

	isci_timer->is_started = TRUE;
	isci_log_message(3, "TIMER", "start %p %d\n", timer, milliseconds);
	callout_reset_sbt(&isci_timer->callout, SBT_1MS * milliseconds, 0,
	    isci_timer_timeout, timer, 0);
}