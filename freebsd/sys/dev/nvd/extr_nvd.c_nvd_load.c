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

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * consumer_handle ; 
 int /*<<< orphan*/  ctrlr_head ; 
 int /*<<< orphan*/  disk_head ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvd_controller_fail ; 
 int /*<<< orphan*/  nvd_lock ; 
 int /*<<< orphan*/  nvd_new_controller ; 
 int /*<<< orphan*/  nvd_new_disk ; 
 int /*<<< orphan*/ * nvme_register_consumer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_use_nvd ; 

__attribute__((used)) static int
nvd_load()
{
	if (!nvme_use_nvd)
		return 0;

	mtx_init(&nvd_lock, "nvd_lock", NULL, MTX_DEF);
	TAILQ_INIT(&ctrlr_head);
	TAILQ_INIT(&disk_head);

	consumer_handle = nvme_register_consumer(nvd_new_disk,
	    nvd_new_controller, NULL, nvd_controller_fail);

	return (consumer_handle != NULL ? 0 : -1);
}