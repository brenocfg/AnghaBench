#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ncp {int /*<<< orphan*/  afq; } ;
struct datalink {scalar_t__ state; TYPE_2__* physical; struct datalink* next; } ;
struct TYPE_4__ {scalar_t__ active; } ;
struct TYPE_6__ {TYPE_1__ mp; } ;
struct bundle {TYPE_3__ ncp; struct datalink* links; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 size_t link_QueueLen (int /*<<< orphan*/ *) ; 
 size_t mp_FillPhysicalQueues (struct bundle*) ; 
 size_t ncp_PushPacket (struct ncp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t ncp_QueueLen (TYPE_3__*) ; 

size_t
ncp_FillPhysicalQueues(struct ncp *ncp, struct bundle *bundle)
{
  size_t total;

  if (bundle->ncp.mp.active)
    total = mp_FillPhysicalQueues(bundle);
  else {
    struct datalink *dl;
    size_t add;

    for (total = 0, dl = bundle->links; dl; dl = dl->next)
      if (dl->state == DATALINK_OPEN) {
        add = link_QueueLen(&dl->physical->link);
        if (add == 0 && dl->physical->out == NULL)
          add = ncp_PushPacket(ncp, &ncp->afq, &dl->physical->link);
        total += add;
      }
  }

  return total + ncp_QueueLen(&bundle->ncp);
}