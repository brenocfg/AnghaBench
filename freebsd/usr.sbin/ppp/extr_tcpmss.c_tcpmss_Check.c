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
struct tcphdr {int dummy; } ;
struct mbuf {int dummy; } ;
struct ip {int ip_hl; scalar_t__ ip_p; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_off; } ;
struct bundle {TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  Enabled (struct bundle*,int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_TCP ; 
 size_t IP_OFFMASK ; 
 int /*<<< orphan*/  MAXMSS (int /*<<< orphan*/ ) ; 
 scalar_t__ MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MSSFixup (struct tcphdr*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_TCPMSSFIXUP ; 
 size_t m_length (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
tcpmss_Check(struct bundle *bundle, struct mbuf *bp)
{
  struct ip *pip;
  size_t hlen, plen;

  if (!Enabled(bundle, OPT_TCPMSSFIXUP))
    return bp;

  bp = m_pullup(bp);
  plen = m_length(bp);
  pip = (struct ip *)MBUF_CTOP(bp);
  hlen = pip->ip_hl << 2;

  /*
   * Check for MSS option only for TCP packets with zero fragment offsets
   * and correct total and header lengths.
   */
  if (pip->ip_p == IPPROTO_TCP && (ntohs(pip->ip_off) & IP_OFFMASK) == 0 &&
      ntohs(pip->ip_len) == plen && hlen <= plen &&
      plen >= sizeof(struct tcphdr) + hlen)
    MSSFixup((struct tcphdr *)(MBUF_CTOP(bp) + hlen), plen - hlen,
             MAXMSS(bundle->iface->mtu));

  return bp;
}