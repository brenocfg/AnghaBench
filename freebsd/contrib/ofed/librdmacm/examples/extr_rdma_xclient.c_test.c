#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct rdma_addrinfo {int dummy; } ;
struct ibv_wc {int dummy; } ;
struct TYPE_14__ {int max_send_wr; int max_recv_wr; int max_send_sge; int max_recv_sge; } ;
struct ibv_qp_init_attr {int sq_sig_all; TYPE_1__ cap; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_19__ {scalar_t__ ai_qp_type; } ;
struct TYPE_18__ {TYPE_4__* event; } ;
struct TYPE_15__ {scalar_t__ private_data; } ;
struct TYPE_16__ {TYPE_2__ conn; } ;
struct TYPE_17__ {TYPE_3__ param; } ;

/* Variables and functions */
 scalar_t__ IBV_QPT_XRC_SEND ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 char* gai_strerror (int) ; 
 TYPE_6__ hints ; 
 TYPE_5__* id ; 
 int /*<<< orphan*/  memset (struct ibv_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int post_send () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rdma_connect (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int rdma_create_ep (TYPE_5__**,struct rdma_addrinfo*,int /*<<< orphan*/ *,struct ibv_qp_init_attr*) ; 
 int /*<<< orphan*/  rdma_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ep (TYPE_5__*) ; 
 int /*<<< orphan*/  rdma_disconnect (TYPE_5__*) ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_get_send_comp (TYPE_5__*,struct ibv_wc*) ; 
 int rdma_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,struct rdma_addrinfo**) ; 
 int /*<<< orphan*/  rdma_reg_msgs (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_msg ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  srqn ; 

__attribute__((used)) static int test(void)
{
	struct rdma_addrinfo *res;
	struct ibv_qp_init_attr attr;
	struct ibv_wc wc;
	int ret;

	ret = rdma_getaddrinfo(server, port, &hints, &res);
	if (ret) {
		printf("rdma_getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	memset(&attr, 0, sizeof attr);
	attr.cap.max_send_wr = attr.cap.max_recv_wr = 1;
	attr.cap.max_send_sge = attr.cap.max_recv_sge = 1;
	attr.sq_sig_all = 1;
	ret = rdma_create_ep(&id, res, NULL, &attr);
	rdma_freeaddrinfo(res);
	if (ret) {
		perror("rdma_create_ep");
		return ret;
	}

	mr = rdma_reg_msgs(id, send_msg, sizeof send_msg);
	if (!mr) {
		perror("rdma_reg_msgs");
		return ret;
	}

	ret = rdma_connect(id, NULL);
	if (ret) {
		perror("rdma_connect");
		return ret;
	}

	if (hints.ai_qp_type == IBV_QPT_XRC_SEND)
		srqn = be32toh(*(__be32 *) id->event->param.conn.private_data);

	ret = post_send();
	if (ret) {
		perror("post_send");
		return ret;
	}

	ret = rdma_get_send_comp(id, &wc);
	if (ret <= 0) {
		perror("rdma_get_recv_comp");
		return ret;
	}

	rdma_disconnect(id);
	rdma_dereg_mr(mr);
	rdma_destroy_ep(id);
	return 0;
}