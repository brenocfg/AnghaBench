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
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  SIGINT ; 
 void SIG_IGN (int) ; 
 int /*<<< orphan*/  SignalBundle ; 
 int /*<<< orphan*/  bundle_Down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sig_signal (int /*<<< orphan*/ ,void (*) (int)) ; 

__attribute__((used)) static void
CloseConnection(int signo)
{
  /* NOTE, these are manual, we've done a setsid() */
  sig_signal(SIGINT, SIG_IGN);
  log_Printf(LogPHASE, "Caught signal %d, abort connection(s)\n", signo);
  bundle_Down(SignalBundle, CLOSE_STAYDOWN);
  sig_signal(SIGINT, CloseConnection);
}