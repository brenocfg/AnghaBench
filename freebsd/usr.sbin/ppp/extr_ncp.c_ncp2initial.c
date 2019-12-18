#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_3__ {int /*<<< orphan*/  fsm; } ;
struct ncp {TYPE_2__ ipv6cp; TYPE_1__ ipcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsm2initial (int /*<<< orphan*/ *) ; 

void
ncp2initial(struct ncp *ncp)
{
  fsm2initial(&ncp->ipcp.fsm);
#ifndef NOINET6
  fsm2initial(&ncp->ipv6cp.fsm);
#endif
}