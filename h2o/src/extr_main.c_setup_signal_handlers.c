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

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int crash_handler_fd ; 
 int /*<<< orphan*/  h2o_set_signal_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_sigfatal ; 
 int /*<<< orphan*/  on_sigterm ; 
 int popen_crash_handler () ; 

__attribute__((used)) static void setup_signal_handlers(void)
{
    h2o_set_signal_handler(SIGTERM, on_sigterm);
    h2o_set_signal_handler(SIGPIPE, SIG_IGN);
#ifdef LIBC_HAS_BACKTRACE
    if ((crash_handler_fd = popen_crash_handler()) == -1)
        crash_handler_fd = 2;
    h2o_set_signal_handler(SIGABRT, on_sigfatal);
    h2o_set_signal_handler(SIGBUS, on_sigfatal);
    h2o_set_signal_handler(SIGFPE, on_sigfatal);
    h2o_set_signal_handler(SIGILL, on_sigfatal);
    h2o_set_signal_handler(SIGSEGV, on_sigfatal);
#endif
}