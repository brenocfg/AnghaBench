#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_send_wr; int max_recv_wr; int max_send_sge; int max_recv_sge; } ;
struct rdma_conn_param {int private_data_len; int /*<<< orphan*/ * private_data; TYPE_1__ cap; } ;
struct rdma_addrinfo {int dummy; } ;
struct ibv_wc {int dummy; } ;
struct ibv_qp_init_attr {int private_data_len; int /*<<< orphan*/ * private_data; TYPE_1__ cap; } ;
struct TYPE_5__ {scalar_t__ ai_qp_type; } ;

/* Variables and functions */
 scalar_t__ IBV_QPT_XRC_RECV ; 
 int create_srq () ; 
 char* gai_strerror (int) ; 
 TYPE_2__ hints ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  listen_id ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rdma_accept (int /*<<< orphan*/ ,struct rdma_conn_param*) ; 
 int rdma_create_ep (int /*<<< orphan*/ *,struct rdma_addrinfo*,int /*<<< orphan*/ *,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rdma_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_get_recv_comp (int /*<<< orphan*/ ,struct ibv_wc*) ; 
 int rdma_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdma_getaddrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,struct rdma_addrinfo**) ; 
 int rdma_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_post_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_reg_msgs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recv_msg ; 
 int /*<<< orphan*/  srqn ; 

__attribute__((used)) static int test(void)
{
	struct rdma_addrinfo *res;
	struct ibv_qp_init_attr attr;
	struct rdma_conn_param param;
	struct ibv_wc wc;
	int ret;

	ret = rdma_getaddrinfo(NULL, port, &hints, &res);
	if (ret) {
		printf("rdma_getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	memset(&attr, 0, sizeof attr);
	attr.cap.max_send_wr = attr.cap.max_recv_wr = 1;
	attr.cap.max_send_sge = attr.cap.max_recv_sge = 1;
	ret = rdma_create_ep(&listen_id, res, NULL, &attr);
	rdma_freeaddrinfo(res);
	if (ret) {
		perror("rdma_create_ep");
		return ret;
	}

	ret = rdma_listen(listen_id, 0);
	if (ret) {
		perror("rdma_listen");
		return ret;
	}

	ret = rdma_get_request(listen_id, &id);
	if (ret) {
		perror("rdma_get_request");
		return ret;
	}

	if (hints.ai_qp_type == IBV_QPT_XRC_RECV) {
		ret = create_srq();
		if (ret)
			return ret;
	}

	mr = rdma_reg_msgs(id, recv_msg, sizeof recv_msg);
	if (!mr) {
		perror("rdma_reg_msgs");
		return ret;
	}

	ret = rdma_post_recv(id, NULL, recv_msg, sizeof recv_msg, mr);
	if (ret) {
		perror("rdma_post_recv");
		return ret;
	}

	memset(&param, 0, sizeof param);
	param.private_data = &srqn;
	param.private_data_len = sizeof srqn;
	ret = rdma_accept(id, &param);
	if (ret) {
		perror("rdma_accept");
		return ret;
	}

	ret = rdma_get_recv_comp(id, &wc);
	if (ret <= 0) {
		perror("rdma_get_recv_comp");
		return ret;
	}

	rdma_disconnect(id);
	rdma_dereg_mr(mr);
	rdma_destroy_ep(id);
	rdma_destroy_ep(listen_id);
	return 0;
}