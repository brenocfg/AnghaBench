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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigusr2_handler ; 

void set_sigusr2_handler (void) {
  struct sigaction act;
  sigset_t signal_set;
  sigemptyset (&signal_set);
  act.sa_handler = sigusr2_handler;
  act.sa_mask = signal_set;
  act.sa_flags = 0;
  assert (!sigaction (SIGUSR2, &act, NULL));
}