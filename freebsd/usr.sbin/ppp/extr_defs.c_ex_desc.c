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
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
ex_desc(int ex)
{
  static char num[12];		/* Used immediately if returned */
  static const char * const desc[] = {
    "normal", "start", "sock", "modem", "dial", "dead", "done",
    "reboot", "errdead", "hangup", "term", "nodial", "nologin",
    "redial", "reconnect"
  };

  if (ex >= 0 && ex < (int)(sizeof desc / sizeof *desc))
    return desc[ex];
  snprintf(num, sizeof num, "%d", ex);
  return num;
}