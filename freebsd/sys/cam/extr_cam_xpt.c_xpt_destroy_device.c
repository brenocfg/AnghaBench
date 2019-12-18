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
struct cam_ed {int /*<<< orphan*/  device_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMDEV ; 
 int /*<<< orphan*/  free (struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xpt_destroy_device(void *context, int pending)
{
	struct cam_ed	*device = context;

	mtx_lock(&device->device_mtx);
	mtx_destroy(&device->device_mtx);
	free(device, M_CAMDEV);
}