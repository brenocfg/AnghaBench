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
 int const SIGINT ; 
 int const SIGTERM ; 
 long long pending_signals ; 
 int /*<<< orphan*/  sigint_immediate_handler ; 
 int /*<<< orphan*/  signal (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_immediate_handler ; 

__attribute__((used)) static void main_sig_handler (const int sig) {
  /* since next operator isn't atomic for 32-bit version, */
  /* sigaction function was used for blocking other signals changing pending_signal variable (sa_mask field) */
  pending_signals |= 1LL << sig;
  if (sig == SIGINT) {
    signal (SIGINT, sigint_immediate_handler);
  }
  if (sig == SIGTERM) {
    signal (SIGTERM, sigterm_immediate_handler);
  }
}