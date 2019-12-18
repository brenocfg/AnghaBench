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
struct iser_rx_desc {int /*<<< orphan*/  rx_sg; } ;
struct ib_conn {int post_recv_buf_count; struct ib_recv_wr* rx_wr; int /*<<< orphan*/  qp; } ;
struct iser_conn {unsigned int rx_desc_head; unsigned int qp_max_recv_dtos; struct iser_rx_desc* rx_descs; struct ib_conn ib_conn; } ;
struct ib_recv_wr {uintptr_t wr_id; int num_sge; struct ib_recv_wr* next; int /*<<< orphan*/ * sg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_ERR (char*,int) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,struct ib_recv_wr**) ; 

int
iser_post_recvm(struct iser_conn *iser_conn, int count)
{
	struct ib_recv_wr *rx_wr, *rx_wr_failed;
	int i, ib_ret;
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	unsigned int my_rx_head = iser_conn->rx_desc_head;
	struct iser_rx_desc *rx_desc;

	for (rx_wr = ib_conn->rx_wr, i = 0; i < count; i++, rx_wr++) {
		rx_desc		= &iser_conn->rx_descs[my_rx_head];
		rx_wr->wr_id	= (uintptr_t)rx_desc;
		rx_wr->sg_list	= &rx_desc->rx_sg;
		rx_wr->num_sge	= 1;
		rx_wr->next	= rx_wr + 1;
		my_rx_head = (my_rx_head + 1) % iser_conn->qp_max_recv_dtos;
	}

	rx_wr--;
	rx_wr->next = NULL; /* mark end of work requests list */

	ib_conn->post_recv_buf_count += count;
	ib_ret	= ib_post_recv(ib_conn->qp, ib_conn->rx_wr, &rx_wr_failed);
	if (ib_ret) {
		ISER_ERR("ib_post_recv failed ret=%d", ib_ret);
		ib_conn->post_recv_buf_count -= count;
	} else
		iser_conn->rx_desc_head = my_rx_head;

	return (ib_ret);
}