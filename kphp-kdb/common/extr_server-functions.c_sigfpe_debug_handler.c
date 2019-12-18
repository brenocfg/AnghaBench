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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwrite (int,char*,int) ; 
 int /*<<< orphan*/  print_backtrace () ; 

void sigfpe_debug_handler (const int sig) {
  kwrite (2, "SIGFPE caught, terminating program\n", 35);
  print_backtrace ();
  exit (EXIT_FAILURE);
}