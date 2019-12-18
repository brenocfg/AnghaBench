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
 int /*<<< orphan*/  Cleanup () ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
CloseSession(int signo)
{
  log_Printf(LogPHASE, "Signal %d, terminate.\n", signo);
  Cleanup();
}