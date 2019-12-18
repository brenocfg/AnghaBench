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
typedef  int /*<<< orphan*/  uint32_t ;
struct port_des {TYPE_2__* nmd; int /*<<< orphan*/  ring; struct overflow_queue* oq; } ;
struct overflow_queue {scalar_t__ n; } ;
struct netmap_slot {int /*<<< orphan*/  buf_idx; } ;
struct TYPE_6__ {size_t output_rings; } ;
struct TYPE_5__ {TYPE_1__* nifp; } ;
struct TYPE_4__ {int /*<<< orphan*/  ni_bufs_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int) ; 
 scalar_t__ NETMAP_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ glob_arg ; 
 int /*<<< orphan*/  nm_close (TYPE_2__*) ; 
 struct netmap_slot oq_deq (struct overflow_queue*) ; 
 struct port_des* ports ; 

__attribute__((used)) static void
free_buffers(void)
{
	int i, tot = 0;
	struct port_des *rxport = &ports[glob_arg.output_rings];

	/* build a netmap free list with the buffers in all the overflow queues */
	for (i = 0; i < glob_arg.output_rings + 1; i++) {
		struct port_des *cp = &ports[i];
		struct overflow_queue *q = cp->oq;

		if (!q)
			continue;

		while (q->n) {
			struct netmap_slot s = oq_deq(q);
			uint32_t *b = (uint32_t *)NETMAP_BUF(cp->ring, s.buf_idx);

			*b = rxport->nmd->nifp->ni_bufs_head;
			rxport->nmd->nifp->ni_bufs_head = s.buf_idx;
			tot++;
		}
	}
	D("added %d buffers to netmap free list", tot);

	for (i = 0; i < glob_arg.output_rings + 1; ++i) {
		nm_close(ports[i].nmd);
	}
}