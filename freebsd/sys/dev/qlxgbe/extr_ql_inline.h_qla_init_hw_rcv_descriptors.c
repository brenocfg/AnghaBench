#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* rds_ring; } ;
struct TYPE_8__ {int num_rds_rings; TYPE_2__ dma_buf; } ;
struct TYPE_9__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;
typedef  int /*<<< orphan*/  q80_recv_desc_t ;
struct TYPE_6__ {scalar_t__ dma_b; } ;

/* Variables and functions */
 int NUM_RX_DESCRIPTORS ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

__attribute__((used)) static __inline void
qla_init_hw_rcv_descriptors(qla_host_t *ha)
{
	int i;

	for (i = 0; i < ha->hw.num_rds_rings; i++) 
		bzero((void *)ha->hw.dma_buf.rds_ring[i].dma_b,
			(sizeof(q80_recv_desc_t) * NUM_RX_DESCRIPTORS));
}