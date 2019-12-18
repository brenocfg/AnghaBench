#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * port; scalar_t__ maxports; scalar_t__ nports; } ;
struct TYPE_5__ {int /*<<< orphan*/ * port; scalar_t__ maxports; scalar_t__ nports; } ;
struct TYPE_7__ {TYPE_2__ udp; TYPE_1__ tcp; } ;
struct TYPE_8__ {TYPE_3__ urgent; } ;
struct ncp {TYPE_4__ cfg; int /*<<< orphan*/  ipv6cp; int /*<<< orphan*/  ipcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6cp_Destroy (int /*<<< orphan*/ *) ; 

void
ncp_Destroy(struct ncp *ncp)
{
  ipcp_Destroy(&ncp->ipcp);
#ifndef NOINET6
  ipv6cp_Destroy(&ncp->ipv6cp);
#endif

  if (ncp->cfg.urgent.tcp.maxports) {
    ncp->cfg.urgent.tcp.nports = ncp->cfg.urgent.tcp.maxports = 0;
    free(ncp->cfg.urgent.tcp.port);
    ncp->cfg.urgent.tcp.port = NULL;
  }
  if (ncp->cfg.urgent.udp.maxports) {
    ncp->cfg.urgent.udp.nports = ncp->cfg.urgent.udp.maxports = 0;
    free(ncp->cfg.urgent.udp.port);
    ncp->cfg.urgent.udp.port = NULL;
  }
}