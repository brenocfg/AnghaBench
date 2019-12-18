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
struct vtnet_rxq {int vtnrx_id; int /*<<< orphan*/  vtnrx_mtx; int /*<<< orphan*/ * vtnrx_sg; int /*<<< orphan*/ * vtnrx_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_destroy_rxq(struct vtnet_rxq *rxq)
{

	rxq->vtnrx_sc = NULL;
	rxq->vtnrx_id = -1;

	if (rxq->vtnrx_sg != NULL) {
		sglist_free(rxq->vtnrx_sg);
		rxq->vtnrx_sg = NULL;
	}

	if (mtx_initialized(&rxq->vtnrx_mtx) != 0)
		mtx_destroy(&rxq->vtnrx_mtx);
}