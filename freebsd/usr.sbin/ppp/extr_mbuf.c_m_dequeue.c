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
typedef  int /*<<< orphan*/  u_long ;
struct mqueue {scalar_t__ len; struct mbuf* top; struct mbuf* last; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct mbuf *
m_dequeue(struct mqueue *q)
{
  struct mbuf *bp;

  log_Printf(LogDEBUG, "m_dequeue: queue len = %lu\n", (u_long)q->len);
  bp = q->top;
  if (bp) {
    q->top = q->top->m_nextpkt;
    q->len--;
    if (q->top == NULL) {
      q->last = q->top;
      if (q->len)
	log_Printf(LogERROR, "m_dequeue: Not zero (%lu)!!!\n",
                   (u_long)q->len);
    }
    bp->m_nextpkt = NULL;
  }

  return bp;
}