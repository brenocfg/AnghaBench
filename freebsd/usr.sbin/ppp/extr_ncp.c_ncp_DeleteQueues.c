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
struct mp {int /*<<< orphan*/  link; } ;
struct ipcp {struct mqueue* Queue; } ;
struct ipv6cp {struct mqueue* Queue; } ;
struct ncp {struct mp mp; struct ipcp ipcp; struct ipv6cp ipv6cp; } ;
struct mqueue {scalar_t__ top; } ;

/* Variables and functions */
 int IPCP_QUEUES (struct ipcp*) ; 
 int IPV6CP_QUEUES (struct ipv6cp*) ; 
 int /*<<< orphan*/  link_DeleteQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_dequeue (struct mqueue*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 

void
ncp_DeleteQueues(struct ncp *ncp)
{
#ifndef NOINET6
  struct ipv6cp *ipv6cp = &ncp->ipv6cp;
#endif
  struct ipcp *ipcp = &ncp->ipcp;
  struct mp *mp = &ncp->mp;
  struct mqueue *q;

  for (q = ipcp->Queue; q < ipcp->Queue + IPCP_QUEUES(ipcp); q++)
    while (q->top)
      m_freem(m_dequeue(q));

#ifndef NOINET6
  for (q = ipv6cp->Queue; q < ipv6cp->Queue + IPV6CP_QUEUES(ipv6cp); q++)
    while (q->top)
      m_freem(m_dequeue(q));
#endif

  link_DeleteQueue(&mp->link);	/* Usually empty anyway */
}