#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; } ;
struct TYPE_5__ {TYPE_1__ ud; } ;
struct rdma_cm_event {TYPE_2__ param; } ;
struct cmatest_node {int connected; int /*<<< orphan*/  ah; int /*<<< orphan*/  pd; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_6__ {int /*<<< orphan*/  connects_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_error () ; 
 int /*<<< orphan*/  ibv_create_ah (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_3__ test ; 

__attribute__((used)) static int resolved_handler(struct cmatest_node *node,
			    struct rdma_cm_event *event)
{
	node->remote_qpn = event->param.ud.qp_num;
	node->remote_qkey = event->param.ud.qkey;
	node->ah = ibv_create_ah(node->pd, &event->param.ud.ah_attr);
	if (!node->ah) {
		printf("udaddy: failure creating address handle\n");
		goto err;
	}

	node->connected = 1;
	test.connects_left--;
	return 0;
err:
	connect_error();
	return -1;
}