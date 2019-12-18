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
struct vif {int dummy; } ;
struct mbuf {int m_len; } ;
struct ip {int ip_hl; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WRITABLE (struct mbuf*) ; 
 int /*<<< orphan*/  VIF_LOCK_ASSERT () ; 
 struct mbuf* m_copypacket (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 
 int /*<<< orphan*/  send_packet (struct vif*,struct mbuf*) ; 

__attribute__((used)) static void
phyint_send(struct ip *ip, struct vif *vifp, struct mbuf *m)
{
    struct mbuf *mb_copy;
    int hlen = ip->ip_hl << 2;

    VIF_LOCK_ASSERT();

    /*
     * Make a new reference to the packet; make sure that
     * the IP header is actually copied, not just referenced,
     * so that ip_output() only scribbles on the copy.
     */
    mb_copy = m_copypacket(m, M_NOWAIT);
    if (mb_copy && (!M_WRITABLE(mb_copy) || mb_copy->m_len < hlen))
	mb_copy = m_pullup(mb_copy, hlen);
    if (mb_copy == NULL)
	return;

    send_packet(vifp, mb_copy);
}