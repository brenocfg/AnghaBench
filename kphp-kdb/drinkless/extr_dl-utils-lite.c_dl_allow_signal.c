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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  dl_passert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_pstr (char*,int const) ; 
 int sigaddset (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dl_allow_signal (const int sig) {
  sigset_t mask;
  sigemptyset (&mask);
  int err = sigaddset (&mask, sig);
  if (err < 0) {
    return -1;
  }
  err = sigprocmask (SIG_UNBLOCK, &mask, NULL);
  dl_passert (err != -1, dl_pstr ("failed to allow signal %d", sig));

  return 0;
}