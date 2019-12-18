#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {TYPE_1__ dgid; } ;
struct TYPE_8__ {int dlid; int sl; TYPE_2__ grh; } ;
struct rdma_ud_param {TYPE_4__ ah_attr; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; } ;
struct cmatest_node {int connected; int /*<<< orphan*/  ah; int /*<<< orphan*/  pd; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_7__ {int /*<<< orphan*/  connects_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  connect_error () ; 
 int /*<<< orphan*/  ibv_create_ah (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__ test ; 

__attribute__((used)) static int join_handler(struct cmatest_node *node,
			struct rdma_ud_param *param)
{
	char buf[40];

	inet_ntop(AF_INET6, param->ah_attr.grh.dgid.raw, buf, 40);
	printf("mckey: joined dgid: %s mlid 0x%x sl %d\n", buf,
		param->ah_attr.dlid, param->ah_attr.sl);

	node->remote_qpn = param->qp_num;
	node->remote_qkey = param->qkey;
	node->ah = ibv_create_ah(node->pd, &param->ah_attr);
	if (!node->ah) {
		printf("mckey: failure creating address handle\n");
		goto err;
	}

	node->connected = 1;
	test.connects_left--;
	return 0;
err:
	connect_error();
	return -1;
}