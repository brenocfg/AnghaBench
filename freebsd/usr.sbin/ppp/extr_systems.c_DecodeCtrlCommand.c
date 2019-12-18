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
 int CTRL_INCLUDE ; 
 int CTRL_UNKNOWN ; 
 char* InterpretArg (char*,char*) ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ issep (char) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
DecodeCtrlCommand(char *line, char *arg)
{
  const char *end;

  if (!strncasecmp(line, "include", 7) && issep(line[7])) {
    end = InterpretArg(line+8, arg);
    if (*end && *end != '#')
      log_Printf(LogWARN, "usage: !include filename\n");
    else
      return CTRL_INCLUDE;
  }
  return CTRL_UNKNOWN;
}