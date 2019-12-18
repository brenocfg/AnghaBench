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
typedef  int /*<<< orphan*/  u_short ;
struct mbuf {scalar_t__ priv; } ;
struct link {int nlayers; scalar_t__ Queue; TYPE_1__** layer; } ;
struct bundle {int dummy; } ;
struct TYPE_2__ {struct mbuf* (* push ) (struct bundle*,struct link*,struct mbuf*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int LINK_QUEUES (struct link*) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  link_AddOutOctets (struct link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_enqueue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_length (struct mbuf*) ; 
 int /*<<< orphan*/  m_pullup (struct mbuf*) ; 
 struct mbuf* stub1 (struct bundle*,struct link*,struct mbuf*,int,int /*<<< orphan*/ *) ; 

void
link_PushPacket(struct link *l, struct mbuf *bp, struct bundle *b, int pri,
                u_short proto)
{
  int layer;

  /*
   * When we ``push'' a packet into the link, it gets processed by the
   * ``push'' function in each layer starting at the top.
   * We never expect the result of a ``push'' to be more than one
   * packet (as we do with ``pull''s).
   */

  if(pri < 0 || (unsigned)pri >= LINK_QUEUES(l))
    pri = 0;

  bp->priv = 0;		/* Adjusted by the async layer ! */
  for (layer = l->nlayers; layer && bp; layer--)
    if (l->layer[layer - 1]->push != NULL)
      bp = (*l->layer[layer - 1]->push)(b, l, bp, pri, &proto);

  if (bp) {
    link_AddOutOctets(l, m_length(bp));
    log_Printf(LogDEBUG, "link_PushPacket: Transmit proto 0x%04x\n", proto);
    m_enqueue(l->Queue + pri, m_pullup(bp));
  }
}