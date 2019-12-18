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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LOG_CRITICAL ; 
 int /*<<< orphan*/  LOG_DEF ; 
 int /*<<< orphan*/  LOG_HISTORY ; 
 int /*<<< orphan*/  LOG_WARNINGS ; 
 int const SIGSEGV ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_log_dump (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dl_print_backtrace () ; 
 int /*<<< orphan*/  dl_print_backtrace_gdb () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void dl_runtime_handler (const int sig) {
  //signal (sig, SIG_DFL);

  fprintf (stderr, "%s caught, terminating program\n", sig == SIGSEGV ? "SIGSEGV" : "SIGABRT");
  fprintf (stderr, "----------------- LOG BEGINS -----------------\n");
  dl_log_dump (LOG_DEF, 0x7f);
  fprintf (stderr, "-----------------  HISTORY   -----------------\n");
  dl_log_dump (LOG_HISTORY, 0x7f);
  fprintf (stderr, "-----------------  WARNINGS  -----------------\n");
  dl_log_dump (LOG_WARNINGS, 0x7f);
  fprintf (stderr, "-----------------  CRITICAL  -----------------\n");
  dl_log_dump (LOG_CRITICAL, 0x7f);
  fprintf (stderr, "----------------- LOG   ENDS -----------------\n");
  dl_print_backtrace();
  dl_print_backtrace_gdb();

  _exit (EXIT_FAILURE);
}