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
typedef  scalar_t__ u_short ;
struct port_range {int nports; int maxports; scalar_t__* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,unsigned int) ; 
 scalar_t__ realloc (scalar_t__*,int) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 

void
ncp_AddUrgentPort(struct port_range *range, u_short port)
{
  u_short *newport;
  unsigned p;

  if (range->nports == range->maxports) {
    range->maxports += 10;
    newport = (u_short *)realloc(range->port,
                                 range->maxports * sizeof(u_short));
    if (newport == NULL) {
      log_Printf(LogERROR, "ncp_AddUrgentPort: realloc: %s\n",
                 strerror(errno));
      range->maxports -= 10;
      return;
    }
    range->port = newport;
  }

  for (p = 0; p < range->nports; p++)
    if (range->port[p] == port) {
      log_Printf(LogWARN, "%u: Port already set to urgent\n", port);
      break;
    } else if (range->port[p] > port) {
      memmove(range->port + p + 1, range->port + p,
              (range->nports - p) * sizeof(u_short));
      range->port[p] = port;
      range->nports++;
      break;
    }

  if (p == range->nports)
    range->port[range->nports++] = port;
}