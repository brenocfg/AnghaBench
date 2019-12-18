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
struct cmdargs {TYPE_1__* prompt; } ;
struct TYPE_2__ {int /*<<< orphan*/  logmask; } ;

/* Variables and functions */
 int LOG_KEPT_LOCAL ; 
 int LOG_KEPT_SYSLOG ; 
 int LogMAX ; 
 int LogMIN ; 
 int log_IsKept (int) ; 
 int log_IsKeptLocal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Name (int) ; 
 int /*<<< orphan*/  prompt_Printf (TYPE_1__*,char*,...) ; 

int
log_ShowLevel(struct cmdargs const *arg)
{
  int i;

  prompt_Printf(arg->prompt, "Log:  ");
  for (i = LogMIN; i <= LogMAX; i++)
    if (log_IsKept(i) & LOG_KEPT_SYSLOG)
      prompt_Printf(arg->prompt, " %s", log_Name(i));

  prompt_Printf(arg->prompt, "\nLocal:");
  for (i = LogMIN; i <= LogMAX; i++)
    if (log_IsKeptLocal(i, arg->prompt->logmask) & LOG_KEPT_LOCAL)
      prompt_Printf(arg->prompt, " %s", log_Name(i));

  prompt_Printf(arg->prompt, "\n");

  return 0;
}