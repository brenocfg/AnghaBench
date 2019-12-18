#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cam_devq {int /*<<< orphan*/  send_mtx; int /*<<< orphan*/  send_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMDEVQ ; 
 int /*<<< orphan*/  camq_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cam_devq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
cam_devq_free(struct cam_devq *devq)
{

	camq_fini(&devq->send_queue);
	mtx_destroy(&devq->send_mtx);
	free(devq, M_CAMDEVQ);
}