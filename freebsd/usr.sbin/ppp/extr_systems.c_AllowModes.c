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
struct cmdargs {int argn; int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int Nam2mode (int /*<<< orphan*/ ) ; 
 int PHYS_ALL ; 
 int PHYS_NONE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int modeok ; 
 int modereq ; 

int
AllowModes(struct cmdargs const *arg)
{
  /* arg->bundle may be NULL (see system_IsValid()) ! */
  int f, mode, allowed;

  allowed = 0;
  for (f = arg->argn; f < arg->argc; f++) {
    mode = Nam2mode(arg->argv[f]);
    if (mode == PHYS_NONE || mode == PHYS_ALL)
      log_Printf(LogWARN, "allow modes: %s: Invalid mode\n", arg->argv[f]);
    else
      allowed |= mode;
  }

  modeok = modereq & allowed ? 1 : 0;
  return 0;
}