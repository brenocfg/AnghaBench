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
struct ibmvtpm_crq_queue {size_t index; size_t num_entry; struct ibmvtpm_crq* crq_addr; } ;
struct ibmvtpm_dev {struct ibmvtpm_crq_queue crq_queue; } ;
struct ibmvtpm_crq {int valid; } ;

/* Variables and functions */
 int VTPM_MSG_RES ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static struct ibmvtpm_crq *ibmvtpm_crq_get_next(struct ibmvtpm_dev *ibmvtpm)
{
	struct ibmvtpm_crq_queue *crq_q = &ibmvtpm->crq_queue;
	struct ibmvtpm_crq *crq = &crq_q->crq_addr[crq_q->index];

	if (crq->valid & VTPM_MSG_RES) {
		if (++crq_q->index == crq_q->num_entry)
			crq_q->index = 0;
		smp_rmb();
	} else
		crq = NULL;
	return crq;
}