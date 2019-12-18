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
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_rdma_dev_lock ; 

void
qlnx_rdma_init(void)
{
	if (!mtx_initialized(&qlnx_rdma_dev_lock)) {
		mtx_init(&qlnx_rdma_dev_lock, "qlnx_rdma_dev_lock", NULL, MTX_DEF);
	}
	return;
}