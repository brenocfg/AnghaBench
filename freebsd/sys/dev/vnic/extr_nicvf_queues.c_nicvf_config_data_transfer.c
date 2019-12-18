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
struct queue_set {int sq_cnt; int cq_cnt; int rbdr_cnt; int rq_cnt; } ;
struct nicvf {struct queue_set* qs; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ nicvf_alloc_resources (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_cmp_queue_config (struct nicvf*,struct queue_set*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_free_resources (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_rbdr_config (struct nicvf*,struct queue_set*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_rcv_queue_config (struct nicvf*,struct queue_set*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_snd_queue_config (struct nicvf*,struct queue_set*,int,int /*<<< orphan*/ ) ; 

int
nicvf_config_data_transfer(struct nicvf *nic, boolean_t enable)
{
	boolean_t disable = FALSE;
	struct queue_set *qs;
	int qidx;

	qs = nic->qs;
	if (qs == NULL)
		return (0);

	if (enable) {
		if (nicvf_alloc_resources(nic) != 0)
			return (ENOMEM);

		for (qidx = 0; qidx < qs->sq_cnt; qidx++)
			nicvf_snd_queue_config(nic, qs, qidx, enable);
		for (qidx = 0; qidx < qs->cq_cnt; qidx++)
			nicvf_cmp_queue_config(nic, qs, qidx, enable);
		for (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
			nicvf_rbdr_config(nic, qs, qidx, enable);
		for (qidx = 0; qidx < qs->rq_cnt; qidx++)
			nicvf_rcv_queue_config(nic, qs, qidx, enable);
	} else {
		for (qidx = 0; qidx < qs->rq_cnt; qidx++)
			nicvf_rcv_queue_config(nic, qs, qidx, disable);
		for (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
			nicvf_rbdr_config(nic, qs, qidx, disable);
		for (qidx = 0; qidx < qs->sq_cnt; qidx++)
			nicvf_snd_queue_config(nic, qs, qidx, disable);
		for (qidx = 0; qidx < qs->cq_cnt; qidx++)
			nicvf_cmp_queue_config(nic, qs, qidx, disable);

		nicvf_free_resources(nic);
	}

	return (0);
}