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
struct rdma_cm_id {int /*<<< orphan*/ * srq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_destroy_srq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_destroy_cqs (struct rdma_cm_id*) ; 

void rdma_destroy_srq(struct rdma_cm_id *id)
{
	ibv_destroy_srq(id->srq);
	id->srq = NULL;
	ucma_destroy_cqs(id);
}