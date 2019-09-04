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
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  kwrite (int,char*,int) ; 
 int /*<<< orphan*/  print_backtrace () ; 
 int /*<<< orphan*/  raise (int const) ; 
 int /*<<< orphan*/  signal (int const,int /*<<< orphan*/ ) ; 

void sigterm_child_handler (const int sig) {
  kwrite (2, "child caught SIGTERM\n", 21);
  print_backtrace ();
  signal (sig, SIG_DFL);
  raise (sig);
}