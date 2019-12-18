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
struct TYPE_2__ {int fd; } ;
struct bundle {TYPE_1__ notify; } ;

/* Variables and functions */
 char EX_NORMAL ; 
 char EX_RECONNECT ; 
 char EX_REDIAL ; 
 int /*<<< orphan*/  LogCHAT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  close (int) ; 
 char* ex_desc (char) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int write (int,char*,int) ; 

void
bundle_Notify(struct bundle *bundle, char c)
{
  if (bundle->notify.fd != -1) {
    int ret;

    ret = write(bundle->notify.fd, &c, 1);
    if (c != EX_REDIAL && c != EX_RECONNECT) {
      if (ret == 1)
        log_Printf(LogCHAT, "Parent notified of %s\n",
                   c == EX_NORMAL ? "success" : "failure");
      else
        log_Printf(LogERROR, "Failed to notify parent of success\n");
      close(bundle->notify.fd);
      bundle->notify.fd = -1;
    } else if (ret == 1)
      log_Printf(LogCHAT, "Parent notified of %s\n", ex_desc(c));
    else
      log_Printf(LogERROR, "Failed to notify parent of %s\n", ex_desc(c));
  }
}