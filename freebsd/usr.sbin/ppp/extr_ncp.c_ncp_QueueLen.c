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
struct ncp {int /*<<< orphan*/  mp; int /*<<< orphan*/  ipv6cp; int /*<<< orphan*/  ipcp; } ;

/* Variables and functions */
 size_t ipcp_QueueLen (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6cp_QueueLen (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_QueueLen (int /*<<< orphan*/ *) ; 

size_t
ncp_QueueLen(struct ncp *ncp)
{
  size_t result;

  result = ipcp_QueueLen(&ncp->ipcp);
#ifndef NOINET6
  result += ipv6cp_QueueLen(&ncp->ipv6cp);
#endif
  result += mp_QueueLen(&ncp->mp);	/* Usually empty */

  return result;
}