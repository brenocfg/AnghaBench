#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct ccb_scsiio {int dummy; } ;
struct TYPE_8__ {TYPE_1__* entries; } ;
struct ccb_hdr {int /*<<< orphan*/  timeout_ch; TYPE_2__ sim_priv; } ;
struct TYPE_9__ {TYPE_4__* vhba; } ;
typedef  TYPE_3__ mptest_t ;
struct TYPE_11__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; int /*<<< orphan*/  actv; } ;
struct TYPE_7__ {TYPE_3__* ptr; } ;

/* Variables and functions */
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_handle_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mptest_act (TYPE_3__*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__ sim_links ; 
 int /*<<< orphan*/  vhba_kick (TYPE_4__*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vhba_task(void *arg, int pending)
{
	mptest_t *vhbas = arg;
	struct ccb_hdr *ccbh;
	int nadded = 0;

	mtx_lock(&vhbas->vhba->lock);
	while ((ccbh = TAILQ_FIRST(&vhbas->vhba->actv)) != NULL) {
		TAILQ_REMOVE(&vhbas->vhba->actv, ccbh, sim_links.tqe);
                mptest_act(vhbas, (struct ccb_scsiio *)ccbh);
		nadded++;
		ccbh->sim_priv.entries[0].ptr = vhbas;
		callout_handle_init(&ccbh->timeout_ch);
	}
	if (nadded) {
		vhba_kick(vhbas->vhba);
	} else {
		while ((ccbh = TAILQ_FIRST(&vhbas->vhba->done)) != NULL) {
			TAILQ_REMOVE(&vhbas->vhba->done, ccbh, sim_links.tqe);
			xpt_done((union ccb *)ccbh);
		}
	}
	mtx_unlock(&vhbas->vhba->lock);
}