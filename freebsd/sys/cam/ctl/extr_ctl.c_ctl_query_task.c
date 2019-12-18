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
struct TYPE_7__ {scalar_t__ tag_num; int /*<<< orphan*/  task_status; } ;
struct TYPE_6__ {scalar_t__ tag_num; } ;
struct TYPE_5__ {size_t targ_mapped_lun; scalar_t__ targ_port; scalar_t__ initid; } ;
struct TYPE_8__ {int flags; TYPE_1__ nexus; } ;
union ctl_io {TYPE_3__ taskio; TYPE_2__ scsiio; TYPE_4__ io_hdr; } ;
typedef  size_t uint32_t ;
struct ctl_softc {int /*<<< orphan*/  ctl_lock; struct ctl_lun** ctl_luns; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  ooa_queue; } ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 struct ctl_softc* CTL_SOFTC (union ctl_io*) ; 
 int /*<<< orphan*/  CTL_TASK_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  CTL_TASK_FUNCTION_SUCCEEDED ; 
 int /*<<< orphan*/  CTL_TASK_LUN_DOES_NOT_EXIST ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_NEXT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 size_t ctl_max_luns ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ooa_links ; 

__attribute__((used)) static int
ctl_query_task(union ctl_io *io, int task_set)
{
	struct ctl_softc *softc = CTL_SOFTC(io);
	union ctl_io *xio;
	struct ctl_lun *lun;
	int found = 0;
	uint32_t targ_lun;

	targ_lun = io->io_hdr.nexus.targ_mapped_lun;
	mtx_lock(&softc->ctl_lock);
	if (targ_lun >= ctl_max_luns ||
	    (lun = softc->ctl_luns[targ_lun]) == NULL) {
		mtx_unlock(&softc->ctl_lock);
		io->taskio.task_status = CTL_TASK_LUN_DOES_NOT_EXIST;
		return (1);
	}
	mtx_lock(&lun->lun_lock);
	mtx_unlock(&softc->ctl_lock);
	for (xio = (union ctl_io *)TAILQ_FIRST(&lun->ooa_queue); xio != NULL;
	     xio = (union ctl_io *)TAILQ_NEXT(&xio->io_hdr, ooa_links)) {

		if ((xio->io_hdr.nexus.targ_port != io->io_hdr.nexus.targ_port)
		 || (xio->io_hdr.nexus.initid != io->io_hdr.nexus.initid)
		 || (xio->io_hdr.flags & CTL_FLAG_ABORT))
			continue;

		if (task_set || xio->scsiio.tag_num == io->taskio.tag_num) {
			found = 1;
			break;
		}
	}
	mtx_unlock(&lun->lun_lock);
	if (found)
		io->taskio.task_status = CTL_TASK_FUNCTION_SUCCEEDED;
	else
		io->taskio.task_status = CTL_TASK_FUNCTION_COMPLETE;
	return (0);
}