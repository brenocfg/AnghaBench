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
struct mppe_state {int flushnext; scalar_t__ stateless; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
MPPEResetOutput(void *v)
{
  struct mppe_state *mop = (struct mppe_state *)v;

  if (mop->stateless)
    log_Printf(LogCCP, "MPPE: Unexpected output channel reset\n");
  else {
    log_Printf(LogCCP, "MPPE: Output channel reset\n");
    mop->flushnext = 1;
  }

  return 0;		/* Ask FSM not to ACK */
}