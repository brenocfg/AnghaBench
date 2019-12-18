#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_vports; int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  devq; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_detach_port (TYPE_1__*,int) ; 

int32_t
ocs_cam_detach(ocs_t *ocs)
{
	int i = 0;

	for (i = (ocs->num_vports); i >= 0; i--) {
		ocs_detach_port(ocs, i);
	}

	cam_simq_free(ocs->devq);

	if (mtx_initialized(&ocs->sim_lock))
		mtx_destroy(&ocs->sim_lock);

	return 0;
}