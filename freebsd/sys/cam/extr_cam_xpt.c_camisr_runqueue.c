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
struct ccb_hdr {int dummy; } ;
struct cam_doneq {int /*<<< orphan*/  cam_doneq_mtx; int /*<<< orphan*/  cam_doneq; } ;
struct TYPE_2__ {int /*<<< orphan*/  stqe; } ;

/* Variables and functions */
 struct ccb_hdr* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cam_doneq* cam_doneqs ; 
 int cam_num_doneqs ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ sim_links ; 
 int /*<<< orphan*/  xpt_done_process (struct ccb_hdr*) ; 

__attribute__((used)) static void
camisr_runqueue(void)
{
	struct	ccb_hdr *ccb_h;
	struct cam_doneq *queue;
	int i;

	/* Process global queues. */
	for (i = 0; i < cam_num_doneqs; i++) {
		queue = &cam_doneqs[i];
		mtx_lock(&queue->cam_doneq_mtx);
		while ((ccb_h = STAILQ_FIRST(&queue->cam_doneq)) != NULL) {
			STAILQ_REMOVE_HEAD(&queue->cam_doneq, sim_links.stqe);
			mtx_unlock(&queue->cam_doneq_mtx);
			xpt_done_process(ccb_h);
			mtx_lock(&queue->cam_doneq_mtx);
		}
		mtx_unlock(&queue->cam_doneq_mtx);
	}
}