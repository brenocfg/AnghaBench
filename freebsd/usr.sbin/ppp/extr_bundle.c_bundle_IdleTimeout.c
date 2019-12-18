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
struct bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  bundle_Close (struct bundle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_StopIdleTimer (struct bundle*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bundle_IdleTimeout(void *v)
{
  struct bundle *bundle = (struct bundle *)v;

  log_Printf(LogPHASE, "Idle timer expired\n");
  bundle_StopIdleTimer(bundle);
  bundle_Close(bundle, NULL, CLOSE_STAYDOWN);
}