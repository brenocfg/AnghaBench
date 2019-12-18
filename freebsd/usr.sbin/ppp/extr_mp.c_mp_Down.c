#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_4__ {TYPE_1__ ccp; } ;
struct mp {scalar_t__ active; int /*<<< orphan*/  peer; struct mbuf* inbufs; TYPE_2__ link; int /*<<< orphan*/  server; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsm2initial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mp_StopAutoloadTimer (struct mp*) ; 
 int /*<<< orphan*/  mpserver_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peerid_Init (int /*<<< orphan*/ *) ; 

void
mp_Down(struct mp *mp)
{
  if (mp->active) {
    struct mbuf *next;

    /* Stop that ! */
    mp_StopAutoloadTimer(mp);

    /* Don't want any more of these */
    mpserver_Close(&mp->server);

    /* CCP goes down with a bang */
    fsm2initial(&mp->link.ccp.fsm);

    /* Received fragments go in the bit-bucket */
    while (mp->inbufs) {
      next = mp->inbufs->m_nextpkt;
      m_freem(mp->inbufs);
      mp->inbufs = next;
    }

    peerid_Init(&mp->peer);
    mp->active = 0;
  }
}