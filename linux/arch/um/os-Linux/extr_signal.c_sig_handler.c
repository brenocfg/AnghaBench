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
 int SIGIO ; 
 int /*<<< orphan*/  SIGIO_MASK ; 
 int /*<<< orphan*/  block_signals_trace () ; 
 int /*<<< orphan*/  set_signals_trace (int) ; 
 int /*<<< orphan*/  sig_handler_common (int,struct siginfo*,int /*<<< orphan*/ *) ; 
 int signals_enabled ; 
 int /*<<< orphan*/  signals_pending ; 

void sig_handler(int sig, struct siginfo *si, mcontext_t *mc)
{
	int enabled;

	enabled = signals_enabled;
	if (!enabled && (sig == SIGIO)) {
		signals_pending |= SIGIO_MASK;
		return;
	}

	block_signals_trace();

	sig_handler_common(sig, si, mc);

	set_signals_trace(enabled);
}