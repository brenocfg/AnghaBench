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
struct krping_cb {int /*<<< orphan*/  pd; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void krping_free_qp(struct krping_cb *cb)
{
	ib_destroy_qp(cb->qp);
	ib_destroy_cq(cb->cq);
	ib_dealloc_pd(cb->pd);
}