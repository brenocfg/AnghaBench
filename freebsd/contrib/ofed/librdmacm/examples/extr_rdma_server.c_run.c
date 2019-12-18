#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int max_send_wr; int max_recv_wr; int max_send_sge; int max_recv_sge; int max_inline_data; } ;
struct rdma_addrinfo {int sq_sig_all; TYPE_1__ cap; int /*<<< orphan*/  ai_port_space; int /*<<< orphan*/  ai_flags; } ;
struct ibv_wc {int dummy; } ;
struct ibv_qp_init_attr {int sq_sig_all; TYPE_1__ cap; int /*<<< orphan*/  ai_port_space; int /*<<< orphan*/  ai_flags; } ;
struct ibv_qp_attr {int sq_sig_all; TYPE_1__ cap; int /*<<< orphan*/  ai_port_space; int /*<<< orphan*/  ai_flags; } ;
struct TYPE_17__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QP_CAP ; 
 int IBV_SEND_INLINE ; 
 int /*<<< orphan*/  RAI_PASSIVE ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 char* gai_strerror (int) ; 
 int ibv_query_qp (int /*<<< orphan*/ ,struct rdma_addrinfo*,int /*<<< orphan*/ ,struct rdma_addrinfo*) ; 
 TYPE_2__* id ; 
 TYPE_2__* listen_id ; 
 int /*<<< orphan*/  memset (struct rdma_addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rdma_accept (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int rdma_create_ep (TYPE_2__**,struct rdma_addrinfo*,int /*<<< orphan*/ *,struct rdma_addrinfo*) ; 
 int /*<<< orphan*/  rdma_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ep (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_get_recv_comp (TYPE_2__*,struct ibv_wc*) ; 
 int rdma_get_request (TYPE_2__*,TYPE_2__**) ; 
 int rdma_get_send_comp (TYPE_2__*,struct ibv_wc*) ; 
 int rdma_getaddrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rdma_addrinfo*,struct rdma_addrinfo**) ; 
 int rdma_listen (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int rdma_post_recv (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rdma_post_send (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_reg_msgs (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recv_msg ; 
 int send_flags ; 
 int /*<<< orphan*/  send_mr ; 
 int /*<<< orphan*/  send_msg ; 

__attribute__((used)) static int run(void)
{
	struct rdma_addrinfo hints, *res;
	struct ibv_qp_init_attr init_attr;
	struct ibv_qp_attr qp_attr;
	struct ibv_wc wc;
	int ret;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = RAI_PASSIVE;
	hints.ai_port_space = RDMA_PS_TCP;
	ret = rdma_getaddrinfo(NULL, port, &hints, &res);
	if (ret) {
		printf("rdma_getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	memset(&init_attr, 0, sizeof init_attr);
	init_attr.cap.max_send_wr = init_attr.cap.max_recv_wr = 1;
	init_attr.cap.max_send_sge = init_attr.cap.max_recv_sge = 1;
	init_attr.cap.max_inline_data = 16;
	init_attr.sq_sig_all = 1;
	ret = rdma_create_ep(&listen_id, res, NULL, &init_attr);
	if (ret) {
		perror("rdma_create_ep");
		goto out_free_addrinfo;
	}

	ret = rdma_listen(listen_id, 0);
	if (ret) {
		perror("rdma_listen");
		goto out_destroy_listen_ep;
	}

	ret = rdma_get_request(listen_id, &id);
	if (ret) {
		perror("rdma_get_request");
		goto out_destroy_listen_ep;
	}

	memset(&qp_attr, 0, sizeof qp_attr);
	memset(&init_attr, 0, sizeof init_attr);
	ret = ibv_query_qp(id->qp, &qp_attr, IBV_QP_CAP,
			   &init_attr);
	if (ret) {
		perror("ibv_query_qp");
		goto out_destroy_accept_ep;
	}
	if (init_attr.cap.max_inline_data >= 16)
		send_flags = IBV_SEND_INLINE;
	else
		printf("rdma_server: device doesn't support IBV_SEND_INLINE, "
		       "using sge sends\n");

	mr = rdma_reg_msgs(id, recv_msg, 16);
	if (!mr) {
		ret = -1;
		perror("rdma_reg_msgs for recv_msg");
		goto out_destroy_accept_ep;
	}
	if ((send_flags & IBV_SEND_INLINE) == 0) {
		send_mr = rdma_reg_msgs(id, send_msg, 16);
		if (!send_mr) {
			ret = -1;
			perror("rdma_reg_msgs for send_msg");
			goto out_dereg_recv;
		}
	}

	ret = rdma_post_recv(id, NULL, recv_msg, 16, mr);
	if (ret) {
		perror("rdma_post_recv");
		goto out_dereg_send;
	}

	ret = rdma_accept(id, NULL);
	if (ret) {
		perror("rdma_accept");
		goto out_dereg_send;
	}

	while ((ret = rdma_get_recv_comp(id, &wc)) == 0);
	if (ret < 0) {
		perror("rdma_get_recv_comp");
		goto out_disconnect;
	}

	ret = rdma_post_send(id, NULL, send_msg, 16, send_mr, send_flags);
	if (ret) {
		perror("rdma_post_send");
		goto out_disconnect;
	}

	while ((ret = rdma_get_send_comp(id, &wc)) == 0);
	if (ret < 0)
		perror("rdma_get_send_comp");
	else
		ret = 0;

out_disconnect:
	rdma_disconnect(id);
out_dereg_send:
	if ((send_flags & IBV_SEND_INLINE) == 0)
		rdma_dereg_mr(send_mr);
out_dereg_recv:
	rdma_dereg_mr(mr);
out_destroy_accept_ep:
	rdma_destroy_ep(id);
out_destroy_listen_ep:
	rdma_destroy_ep(listen_id);
out_free_addrinfo:
	rdma_freeaddrinfo(res);
	return ret;
}