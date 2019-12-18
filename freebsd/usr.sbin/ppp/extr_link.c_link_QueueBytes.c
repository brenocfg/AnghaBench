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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct link {TYPE_1__* Queue; } ;
struct TYPE_2__ {size_t len; struct mbuf* top; } ;

/* Variables and functions */
 unsigned int LINK_QUEUES (struct link*) ; 
 scalar_t__ m_length (struct mbuf*) ; 

size_t
link_QueueBytes(struct link *l)
{
  unsigned i;
  size_t len, bytes;
  struct mbuf *m;

  bytes = 0;
  for (i = 0, len = 0; i < LINK_QUEUES(l); i++) {
    len = l->Queue[i].len;
    m = l->Queue[i].top;
    while (len--) {
      bytes += m_length(m);
      m = m->m_nextpkt;
    }
  }

  return bytes;
}