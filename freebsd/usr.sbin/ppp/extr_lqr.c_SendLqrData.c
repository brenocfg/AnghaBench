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
struct mbuf {int m_len; int m_offset; } ;
struct lqrdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; int /*<<< orphan*/  bundle; } ;
struct lcp {TYPE_1__ fsm; } ;

/* Variables and functions */
 scalar_t__ LINK_QUEUES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_LQROUT ; 
 int /*<<< orphan*/  PROTO_LQR ; 
 int acf_WrapperOctets (struct lcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_PushPacket (int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 int proto_WrapperOctets (struct lcp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SendLqrData(struct lcp *lcp)
{
  struct mbuf *bp;
  int extra;

  extra = proto_WrapperOctets(lcp, PROTO_LQR) +
          acf_WrapperOctets(lcp, PROTO_LQR);
  bp = m_get(sizeof(struct lqrdata) + extra, MB_LQROUT);
  bp->m_len -= extra;
  bp->m_offset += extra;

  /*
   * Send on the highest priority queue.  We send garbage - the real data
   * is written by lqr_LayerPush() where we know how to fill in all the
   * fields.  Note, lqr_LayerPush() ``knows'' that we're pushing onto the
   * highest priority queue, and factors out packet & octet values from
   * other queues!
   */
  link_PushPacket(lcp->fsm.link, bp, lcp->fsm.bundle,
                  LINK_QUEUES(lcp->fsm.link) - 1, PROTO_LQR);
}