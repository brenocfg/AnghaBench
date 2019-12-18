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
struct rping_cb {int /*<<< orphan*/  pd; int /*<<< orphan*/  channel; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_comp_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rping_free_qp(struct rping_cb *cb)
{
	ibv_destroy_qp(cb->qp);
	ibv_destroy_cq(cb->cq);
	ibv_destroy_comp_channel(cb->channel);
	ibv_dealloc_pd(cb->pd);
}