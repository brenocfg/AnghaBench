#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; scalar_t__** argv; TYPE_1__* cx; } ;
struct TYPE_2__ {int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ physical_SetSpeed (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  physical_SetSync (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (scalar_t__*,char*) ; 
 long strtol (scalar_t__*,char**,int) ; 

__attribute__((used)) static int
SetModemSpeed(struct cmdargs const *arg)
{
  long speed;
  char *end;

  if (arg->argc > arg->argn && *arg->argv[arg->argn]) {
    if (arg->argc > arg->argn+1) {
      log_Printf(LogWARN, "SetModemSpeed: Too many arguments\n");
      return -1;
    }
    if (strcasecmp(arg->argv[arg->argn], "sync") == 0) {
      physical_SetSync(arg->cx->physical);
      return 0;
    }
    end = NULL;
    speed = strtol(arg->argv[arg->argn], &end, 10);
    if (*end || speed < 0) {
      log_Printf(LogWARN, "SetModemSpeed: Bad argument \"%s\"",
                arg->argv[arg->argn]);
      return -1;
    }
    if (physical_SetSpeed(arg->cx->physical, speed))
      return 0;
    log_Printf(LogWARN, "%s: Invalid speed\n", arg->argv[arg->argn]);
  } else
    log_Printf(LogWARN, "SetModemSpeed: No speed specified\n");

  return -1;
}