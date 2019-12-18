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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int ;
struct cam_sim {struct cam_devq* devq; } ;
struct TYPE_2__ {int /*<<< orphan*/  qfrozen_cnt; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; TYPE_1__ send_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

u_int32_t
xpt_freeze_simq(struct cam_sim *sim, u_int count)
{
	struct cam_devq	*devq;
	uint32_t	 freeze;

	devq = sim->devq;
	mtx_lock(&devq->send_mtx);
	freeze = (devq->send_queue.qfrozen_cnt += count);
	mtx_unlock(&devq->send_mtx);
	return (freeze);
}