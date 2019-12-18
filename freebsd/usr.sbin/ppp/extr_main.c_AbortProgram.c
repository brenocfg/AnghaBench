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
 scalar_t__ SignalBundle ; 
 int /*<<< orphan*/  bundle_Close (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_Destroy (scalar_t__) ; 
 int /*<<< orphan*/  ex_desc (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  log_Close () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_Close (scalar_t__) ; 

void
AbortProgram(int excode)
{
  if (SignalBundle)
    server_Close(SignalBundle);
  log_Printf(LogPHASE, "PPP Terminated (%s).\n", ex_desc(excode));
  if (SignalBundle) {
    bundle_Close(SignalBundle, NULL, CLOSE_STAYDOWN);
    bundle_Destroy(SignalBundle);
  }
  log_Close();
  exit(excode);
}