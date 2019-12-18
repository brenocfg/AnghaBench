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
typedef  uintptr_t uint64_t ;
struct pcap_rdmasniff {int /*<<< orphan*/  qp; TYPE_1__* mr; } ;
struct ibv_sge {uintptr_t length; uintptr_t addr; int /*<<< orphan*/  lkey; } ;
struct ibv_recv_wr {uintptr_t wr_id; int num_sge; int /*<<< orphan*/ * next; struct ibv_sge* sg_list; } ;
struct TYPE_5__ {scalar_t__ buffer; struct pcap_rdmasniff* priv; } ;
typedef  TYPE_2__ pcap_t ;
struct TYPE_4__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 uintptr_t RDMASNIFF_RECEIVE_SIZE ; 
 int /*<<< orphan*/  ibv_post_recv (int /*<<< orphan*/ ,struct ibv_recv_wr*,struct ibv_recv_wr**) ; 

__attribute__((used)) static void
rdmasniff_post_recv(pcap_t *handle, uint64_t wr_id)
{
	struct pcap_rdmasniff *priv = handle->priv;
	struct ibv_sge sg_entry;
	struct ibv_recv_wr wr, *bad_wr;

	sg_entry.length = RDMASNIFF_RECEIVE_SIZE;
	sg_entry.addr = (uintptr_t) handle->buffer + RDMASNIFF_RECEIVE_SIZE * wr_id;
	sg_entry.lkey = priv->mr->lkey;

	wr.wr_id = wr_id;
	wr.num_sge = 1;
	wr.sg_list = &sg_entry;
	wr.next = NULL;

	ibv_post_recv(priv->qp, &wr, &bad_wr);
}