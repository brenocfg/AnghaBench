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
struct rping_cb {int /*<<< orphan*/  start_buf; int /*<<< orphan*/  start_mr; int /*<<< orphan*/  server; int /*<<< orphan*/  rdma_buf; int /*<<< orphan*/  rdma_mr; int /*<<< orphan*/  send_mr; int /*<<< orphan*/  recv_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*,struct rping_cb*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_dereg_mr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rping_free_buffers(struct rping_cb *cb)
{
	DEBUG_LOG("rping_free_buffers called on cb %p\n", cb);
	ibv_dereg_mr(cb->recv_mr);
	ibv_dereg_mr(cb->send_mr);
	ibv_dereg_mr(cb->rdma_mr);
	free(cb->rdma_buf);
	if (!cb->server) {
		ibv_dereg_mr(cb->start_mr);
		free(cb->start_buf);
	}
}