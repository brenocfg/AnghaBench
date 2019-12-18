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
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qlnx_host_list ; 
 int /*<<< orphan*/  qlnx_rdma_dev_lock ; 

void
qlnx_rdma_deinit(void)
{
	if (mtx_initialized(&qlnx_rdma_dev_lock) && (qlnx_host_list == NULL)) {
		mtx_destroy(&qlnx_rdma_dev_lock);
	}
	return;
}