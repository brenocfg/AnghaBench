#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* entries; } ;
struct ccb_hdr {TYPE_2__ sim_priv; } ;
struct TYPE_8__ {int nact; TYPE_4__* vhba; int /*<<< orphan*/  inproc; } ;
typedef  TYPE_3__ mptest_t ;
struct TYPE_10__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; } ;
struct TYPE_6__ {TYPE_3__* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__ sim_links ; 
 int /*<<< orphan*/  vhba_kick (TYPE_4__*) ; 

__attribute__((used)) static void
vhba_iodelay(void *arg)
{
	struct ccb_hdr *ccbh = arg;
	mptest_t *vhbas = ccbh->sim_priv.entries[0].ptr;

	mtx_lock(&vhbas->vhba->lock);
	TAILQ_REMOVE(&vhbas->inproc, ccbh, sim_links.tqe);
	TAILQ_INSERT_TAIL(&vhbas->vhba->done, ccbh, sim_links.tqe);
	vhbas->nact -= 1;
	vhba_kick(vhbas->vhba);
	mtx_unlock(&vhbas->vhba->lock);
}