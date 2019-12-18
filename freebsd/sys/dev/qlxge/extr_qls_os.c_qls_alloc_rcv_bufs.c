#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rx_buf; } ;
typedef  TYPE_1__ qla_rx_ring_t ;
typedef  int /*<<< orphan*/  qla_rx_buf_t ;
struct TYPE_7__ {int num_rx_rings; TYPE_1__* rx_ring; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int NUM_RX_DESCRIPTORS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int qls_alloc_rcv_mbufs (TYPE_2__*,int) ; 
 int /*<<< orphan*/  qls_free_rcv_bufs (TYPE_2__*) ; 

__attribute__((used)) static int
qls_alloc_rcv_bufs(qla_host_t *ha)
{
	int		r, ret = 0;
	qla_rx_ring_t	*rxr;

	for (r = 0; r < ha->num_rx_rings; r++) {
		rxr = &ha->rx_ring[r];
		bzero(rxr->rx_buf, (sizeof(qla_rx_buf_t) * NUM_RX_DESCRIPTORS));
	}

	for (r = 0; r < ha->num_rx_rings; r++) {

		ret = qls_alloc_rcv_mbufs(ha, r);

		if (ret)
			qls_free_rcv_bufs(ha);
	}

	return (ret);
}