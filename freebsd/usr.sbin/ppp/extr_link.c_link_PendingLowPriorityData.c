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
struct mqueue {size_t len; struct mbuf* top; } ;
struct mbuf {scalar_t__ priv; struct mbuf* m_nextpkt; } ;
struct link {struct mqueue* Queue; } ;

/* Variables and functions */
 struct mqueue* LINK_HIGHQ (struct link*) ; 
 scalar_t__ m_length (struct mbuf*) ; 

void
link_PendingLowPriorityData(struct link *l, size_t *pkts, size_t *octets)
{
  struct mqueue *queue, *highest;
  struct mbuf *m;
  size_t len;

  /*
   * This is all rfc1989 stuff... because our LQR packet is going to bypass
   * everything that's not in the highest priority queue, we must be able to
   * subtract that data from our outgoing packet/octet counts.  However,
   * we've already async-encoded our data at this point, but the async
   * encodings MUSTn't be a part of the LQR-reported payload :(  So, we have
   * the async layer record how much it's padded the packet in the mbuf's
   * priv field, and when we calculate our outgoing LQR values we subtract
   * this value for each packet from the octet count sent.
   */

  highest = LINK_HIGHQ(l);
  *pkts = *octets = 0;
  for (queue = l->Queue; queue < highest; queue++) {
    len = queue->len;
    *pkts += len;
    for (m = queue->top; len--; m = m->m_nextpkt)
      *octets += m_length(m) - m->priv;
  }
}