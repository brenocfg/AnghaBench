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
typedef  int /*<<< orphan*/  u_long ;
struct mbuf {int dummy; } ;
struct link {TYPE_1__* Queue; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int LINK_QUEUES (struct link*) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_dequeue (TYPE_1__*) ; 

struct mbuf *
link_Dequeue(struct link *l)
{
  int pri;
  struct mbuf *bp;

  for (bp = NULL, pri = LINK_QUEUES(l) - 1; pri >= 0; pri--)
    if (l->Queue[pri].len) {
      bp = m_dequeue(l->Queue + pri);
      log_Printf(LogDEBUG, "link_Dequeue: Dequeued from queue %d,"
                " containing %lu more packets\n", pri,
                (u_long)l->Queue[pri].len);
      break;
    }

  return bp;
}