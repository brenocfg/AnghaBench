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
struct ncp {int /*<<< orphan*/  ipv6cp; int /*<<< orphan*/  ipcp; } ;
struct link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipcp_SetLink (int /*<<< orphan*/ *,struct link*) ; 
 int /*<<< orphan*/  ipv6cp_SetLink (int /*<<< orphan*/ *,struct link*) ; 

void
ncp_SetLink(struct ncp *ncp, struct link *l)
{
  ipcp_SetLink(&ncp->ipcp, l);
#ifndef NOINET6
  ipv6cp_SetLink(&ncp->ipv6cp, l);
#endif
}