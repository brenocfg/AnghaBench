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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  sigusr2_handler ; 

__attribute__((used)) static void signals_init (void) {
  set_debug_handlers ();
  struct sigaction sa;
  memset (&sa, 0, sizeof (sa));
  sa.sa_handler = sigint_handler;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGTERM);
  sigaction (SIGINT, &sa, NULL);

  sa.sa_handler = sigterm_handler;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGINT);
  sigaction (SIGTERM, &sa, NULL);

  sa.sa_handler = SIG_IGN;
  sigaction (SIGPIPE, &sa, NULL);
  sigaction (SIGPOLL, &sa, NULL);
  sigaction (SIGUSR1, &sa, NULL);

  sa.sa_handler = sigusr1_handler;
  sigemptyset (&sa.sa_mask);
  sigaction (SIGUSR1, &sa, NULL);

  sa.sa_handler = sigusr2_handler;
  sigemptyset (&sa.sa_mask);
  sigaction (SIGUSR2, &sa, NULL);

}