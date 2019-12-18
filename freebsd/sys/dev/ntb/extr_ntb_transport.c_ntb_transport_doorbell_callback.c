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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_transport_qp {int /*<<< orphan*/  rxc_db_work; int /*<<< orphan*/  rxc_tq; scalar_t__ link_is_up; } ;
struct ntb_transport_ctx {int qp_bitmap; struct ntb_transport_qp* qp_vec; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ffsll (int) ; 
 int /*<<< orphan*/  ntb_db_clear (int /*<<< orphan*/ ,int) ; 
 int ntb_db_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_set_mask (int /*<<< orphan*/ ,int) ; 
 int ntb_db_vector_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ntb_transport_doorbell_callback(void *data, uint32_t vector)
{
	struct ntb_transport_ctx *nt = data;
	struct ntb_transport_qp *qp;
	uint64_t vec_mask;
	unsigned qp_num;

	vec_mask = ntb_db_vector_mask(nt->dev, vector);
	vec_mask &= nt->qp_bitmap;
	if ((vec_mask & (vec_mask - 1)) != 0)
		vec_mask &= ntb_db_read(nt->dev);
	if (vec_mask != 0) {
		ntb_db_set_mask(nt->dev, vec_mask);
		ntb_db_clear(nt->dev, vec_mask);
	}
	while (vec_mask != 0) {
		qp_num = ffsll(vec_mask) - 1;

		qp = &nt->qp_vec[qp_num];
		if (qp->link_is_up)
			taskqueue_enqueue(qp->rxc_tq, &qp->rxc_db_work);

		vec_mask &= ~(1ull << qp_num);
	}
}