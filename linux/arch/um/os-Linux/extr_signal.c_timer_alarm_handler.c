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
struct siginfo {int dummy; } ;
typedef  int /*<<< orphan*/  mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM_MASK ; 
 int /*<<< orphan*/  block_signals_trace () ; 
 int /*<<< orphan*/  set_signals_trace (int) ; 
 int /*<<< orphan*/  signals_active ; 
 int signals_enabled ; 
 int /*<<< orphan*/  signals_pending ; 
 int /*<<< orphan*/  timer_real_alarm_handler (int /*<<< orphan*/ *) ; 

void timer_alarm_handler(int sig, struct siginfo *unused_si, mcontext_t *mc)
{
	int enabled;

	enabled = signals_enabled;
	if (!signals_enabled) {
		signals_pending |= SIGALRM_MASK;
		return;
	}

	block_signals_trace();

	signals_active |= SIGALRM_MASK;

	timer_real_alarm_handler(mc);

	signals_active &= ~SIGALRM_MASK;

	set_signals_trace(enabled);
}