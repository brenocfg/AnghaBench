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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  cdw0; } ;
struct nvme_pt_command {struct mtx* driver_lock; TYPE_1__ cpl; } ;
struct nvme_completion {int /*<<< orphan*/  status; int /*<<< orphan*/  cdw0; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_STATUS_P_MASK ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  wakeup (struct nvme_pt_command*) ; 

__attribute__((used)) static void
nvme_pt_done(void *arg, const struct nvme_completion *cpl)
{
	struct nvme_pt_command *pt = arg;
	struct mtx *mtx = pt->driver_lock;
	uint16_t status;

	bzero(&pt->cpl, sizeof(pt->cpl));
	pt->cpl.cdw0 = cpl->cdw0;

	status = cpl->status;
	status &= ~NVME_STATUS_P_MASK;
	pt->cpl.status = status;

	mtx_lock(mtx);
	pt->driver_lock = NULL;
	wakeup(pt);
	mtx_unlock(mtx);
}