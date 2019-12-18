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
typedef  int /*<<< orphan*/  const sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  assert (int) ; 
 long long pending_signals ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void pending_signals_clear_bit (const sigset_t *ss, const int sig) {
  sigset_t old;
  int r = sigprocmask (SIG_BLOCK, ss, &old);
  assert (!r);
  pending_signals &= ~(1LL << sig);
  r = sigprocmask (SIG_SETMASK, &old, NULL);
  assert (!r);
}