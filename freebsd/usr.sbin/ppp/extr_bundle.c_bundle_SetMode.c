#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct datalink {TYPE_4__* physical; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct TYPE_10__ {TYPE_1__ peer_ip; } ;
struct TYPE_8__ {TYPE_5__ ipcp; } ;
struct TYPE_7__ {int all; } ;
struct bundle {scalar_t__ phase; TYPE_3__ ncp; TYPE_2__ phys_type; } ;
struct TYPE_9__ {int type; } ;

/* Variables and functions */
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ PHASE_NETWORK ; 
 int PHYS_AUTO ; 
 int /*<<< orphan*/  bundle_LinksRemoved (struct bundle*) ; 
 int /*<<< orphan*/  datalink_SetMode (struct datalink*,int) ; 
 int /*<<< orphan*/  ipcp_InterfaceUp (TYPE_5__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode2Nam (int) ; 

int
bundle_SetMode(struct bundle *bundle, struct datalink *dl, int mode)
{
  int omode;

  omode = dl->physical->type;
  if (omode == mode)
    return 1;

  if (mode == PHYS_AUTO && !(bundle->phys_type.all & PHYS_AUTO))
    /* First auto link */
    if (bundle->ncp.ipcp.peer_ip.s_addr == INADDR_ANY) {
      log_Printf(LogWARN, "You must `set ifaddr' or `open' before"
                 " changing mode to %s\n", mode2Nam(mode));
      return 0;
    }

  if (!datalink_SetMode(dl, mode))
    return 0;

  if (mode == PHYS_AUTO && !(bundle->phys_type.all & PHYS_AUTO) &&
      bundle->phase != PHASE_NETWORK)
    /* First auto link, we need an interface */
    ipcp_InterfaceUp(&bundle->ncp.ipcp);

  /* Regenerate phys_type and adjust idle timer */
  bundle_LinksRemoved(bundle);

  return 1;
}