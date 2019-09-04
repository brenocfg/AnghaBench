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
 int const SIGSEGV ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_print_backtrace () ; 
 int /*<<< orphan*/  dl_print_backtrace_gdb () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void runtime_handler (const int sig) {
  fprintf (stderr, "%s caught, terminating program\n", sig == SIGSEGV ? "SIGSEGV" : "SIGABRT");
  dl_print_backtrace();
  dl_print_backtrace_gdb();
  _exit (EXIT_FAILURE);
}