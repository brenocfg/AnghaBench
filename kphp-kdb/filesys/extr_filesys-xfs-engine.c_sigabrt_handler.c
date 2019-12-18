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
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwrite (int,char const*,int) ; 
 int /*<<< orphan*/  print_backtrace () ; 
 int /*<<< orphan*/  unlock_pid_file () ; 

void sigabrt_handler (const int sig) {
  static const char message[] = "SIGABRT caught, terminating program\n";
  kwrite (2, message, sizeof (message) - (size_t)1);
  print_backtrace ();
  unlock_pid_file ();
  exit (EXIT_FAILURE);
}