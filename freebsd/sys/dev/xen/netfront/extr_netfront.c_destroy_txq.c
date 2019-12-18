#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sring; } ;
struct netfront_txq {int /*<<< orphan*/  tq; int /*<<< orphan*/  br; TYPE_1__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
destroy_txq(struct netfront_txq *txq)
{

	free(txq->ring.sring, M_DEVBUF);
	buf_ring_free(txq->br, M_DEVBUF);
	taskqueue_drain_all(txq->tq);
	taskqueue_free(txq->tq);
}