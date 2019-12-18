#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct datalink {int state; TYPE_4__* physical; int /*<<< orphan*/  peer; } ;
struct TYPE_6__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_5__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_7__ {TYPE_2__ lcp; TYPE_1__ ccp; } ;
struct TYPE_8__ {TYPE_3__ link; } ;

/* Variables and functions */
#define  DATALINK_AUTH 131 
#define  DATALINK_CBCP 130 
#define  DATALINK_LCP 129 
#define  DATALINK_OPEN 128 
 int DATALINK_OPENING ; 
 int /*<<< orphan*/  datalink_ComeDown (struct datalink*,int) ; 
 int /*<<< orphan*/  fsm2initial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peerid_Init (int /*<<< orphan*/ *) ; 

void
datalink_Down(struct datalink *dl, int how)
{
  /* Carrier is lost */
  switch (dl->state) {
    case DATALINK_OPEN:
      peerid_Init(&dl->peer);
      fsm2initial(&dl->physical->link.ccp.fsm);
      /* FALLTHROUGH */

    case DATALINK_CBCP:
    case DATALINK_AUTH:
    case DATALINK_LCP:
      fsm2initial(&dl->physical->link.lcp.fsm);
      if (dl->state == DATALINK_OPENING)
        return;			/* we're doing a callback... */
      /* FALLTHROUGH */

    default:
      datalink_ComeDown(dl, how);
  }
}