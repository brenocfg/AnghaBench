#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * sim; int /*<<< orphan*/ * devq; int /*<<< orphan*/  done; int /*<<< orphan*/  actv; } ;
typedef  TYPE_1__ vhba_softc_t ;

/* Variables and functions */
 scalar_t__ CAM_SUCCESS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VHBA_MAXCMDS ; 
 int /*<<< orphan*/  VHBA_MOD ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhba_action ; 
 int /*<<< orphan*/  vhba_init (TYPE_1__*) ; 
 int /*<<< orphan*/  vhba_poll ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vhba_attach(vhba_softc_t *vhba)
{
	TAILQ_INIT(&vhba->actv);
	TAILQ_INIT(&vhba->done);
	vhba->devq = cam_simq_alloc(VHBA_MAXCMDS);
	if (vhba->devq == NULL) {
		return (ENOMEM);
	}
	vhba->sim = cam_sim_alloc(vhba_action, vhba_poll, VHBA_MOD, vhba, 0, &vhba->lock, VHBA_MAXCMDS, VHBA_MAXCMDS, vhba->devq);
	if (vhba->sim == NULL) {
		cam_simq_free(vhba->devq);
		return (ENOMEM);
	}
	vhba_init(vhba);
	mtx_lock(&vhba->lock);
	if (xpt_bus_register(vhba->sim, 0, 0) != CAM_SUCCESS) {
		cam_sim_free(vhba->sim, TRUE);
		mtx_unlock(&vhba->lock);
		return (EIO);
	}
	mtx_unlock(&vhba->lock);
	return (0);
}