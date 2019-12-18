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
struct ipcp {unsigned int Queue; } ;
struct ipv6cp {unsigned int Queue; } ;
struct ncp {struct ipcp ipcp; struct ipv6cp ipv6cp; } ;
struct mbuf {int m_offset; int m_len; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int IPCP_QUEUES (struct ipcp*) ; 
 unsigned int IPV6CP_QUEUES (struct ipcp*) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_IPOUT ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  m_enqueue (unsigned int,struct mbuf*) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

void
ncp_Enqueue(struct ncp *ncp, int af, unsigned pri, char *ptr, int count)
{
#ifndef NOINET6
  struct ipv6cp *ipv6cp = &ncp->ipv6cp;
#endif
  struct ipcp *ipcp = &ncp->ipcp;
  struct mbuf *bp;

  /*
   * We allocate an extra 6 bytes, four at the front and two at the end.
   * This is an optimisation so that we need to do less work in
   * m_prepend() in acf_LayerPush() and proto_LayerPush() and
   * appending in hdlc_LayerPush().
   */

  switch (af) {
  case AF_INET:
    if (pri >= IPCP_QUEUES(ipcp)) {
      log_Printf(LogERROR, "Can't store in ip queue %u\n", pri);
      break;
    }

    bp = m_get(count + 6, MB_IPOUT);
    bp->m_offset += 4;
    bp->m_len -= 6;
    memcpy(MBUF_CTOP(bp), ptr, count);
    m_enqueue(ipcp->Queue + pri, bp);
    break;

#ifndef NOINET6
  case AF_INET6:
    if (pri >= IPV6CP_QUEUES(ipcp)) {
      log_Printf(LogERROR, "Can't store in ipv6 queue %u\n", pri);
      break;
    }

    bp = m_get(count + 6, MB_IPOUT);
    bp->m_offset += 4;
    bp->m_len -= 6;
    memcpy(MBUF_CTOP(bp), ptr, count);
    m_enqueue(ipv6cp->Queue + pri, bp);
    break;
#endif

  default:
      log_Printf(LogERROR, "Can't enqueue protocol family %d\n", af);
  }
}