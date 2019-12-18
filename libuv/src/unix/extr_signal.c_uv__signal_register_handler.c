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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_handler ; 

__attribute__((used)) static int uv__signal_register_handler(int signum, int oneshot) {
  /* When this function is called, the signal lock must be held. */
  struct sigaction sa;

  /* XXX use a separate signal stack? */
  memset(&sa, 0, sizeof(sa));
  if (sigfillset(&sa.sa_mask))
    abort();
  sa.sa_handler = uv__signal_handler;
  sa.sa_flags = SA_RESTART;
  if (oneshot)
    sa.sa_flags |= SA_RESETHAND;

  /* XXX save old action so we can restore it later on? */
  if (sigaction(signum, &sa, NULL))
    return UV__ERR(errno);

  return 0;
}