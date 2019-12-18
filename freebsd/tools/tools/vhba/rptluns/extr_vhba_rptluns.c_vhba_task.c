#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vhba; } ;
typedef  TYPE_2__ vhbarptluns_t ;
typedef  union ccb {int dummy; } ccb ;
struct ccb_scsiio {int dummy; } ;
struct ccb_hdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; int /*<<< orphan*/  actv; } ;

/* Variables and functions */
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__ sim_links ; 
 int /*<<< orphan*/  vhbarptluns_act (TYPE_2__*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vhba_task(void *arg, int pending)
{
	vhbarptluns_t *vhbas = arg;
	struct ccb_hdr *ccbh;

	mtx_lock(&vhbas->vhba->lock);
	while ((ccbh = TAILQ_FIRST(&vhbas->vhba->actv)) != NULL) {
		TAILQ_REMOVE(&vhbas->vhba->actv, ccbh, sim_links.tqe);
                vhbarptluns_act(vhbas, (struct ccb_scsiio *)ccbh);
	}
	while ((ccbh = TAILQ_FIRST(&vhbas->vhba->done)) != NULL) {
		TAILQ_REMOVE(&vhbas->vhba->done, ccbh, sim_links.tqe);
		xpt_done((union ccb *)ccbh);
	}
	mtx_unlock(&vhbas->vhba->lock);
}