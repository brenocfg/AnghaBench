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
struct queue_set {int /*<<< orphan*/  sq_cnt; int /*<<< orphan*/  rq_cnt; int /*<<< orphan*/  cq_len; int /*<<< orphan*/  sq_len; int /*<<< orphan*/  rbdr_len; int /*<<< orphan*/  cq_cnt; int /*<<< orphan*/  rbdr_cnt; } ;
struct nicvf {int /*<<< orphan*/  tx_queues; int /*<<< orphan*/  rx_queues; struct queue_set* qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_QUEUE_CNT ; 
 int /*<<< orphan*/  CMP_QUEUE_LEN ; 
 int /*<<< orphan*/  M_NICVF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RBDR_CNT ; 
 int /*<<< orphan*/  RCV_BUF_COUNT ; 
 int /*<<< orphan*/  RCV_QUEUE_CNT ; 
 int /*<<< orphan*/  SND_QUEUE_CNT ; 
 int /*<<< orphan*/  SND_QUEUE_LEN ; 
 struct queue_set* malloc (int,int /*<<< orphan*/ ,int) ; 

int
nicvf_set_qset_resources(struct nicvf *nic)
{
	struct queue_set *qs;

	qs = malloc(sizeof(*qs), M_NICVF, (M_ZERO | M_WAITOK));
	nic->qs = qs;

	/* Set count of each queue */
	qs->rbdr_cnt = RBDR_CNT;
	qs->rq_cnt = RCV_QUEUE_CNT;

	qs->sq_cnt = SND_QUEUE_CNT;
	qs->cq_cnt = CMP_QUEUE_CNT;

	/* Set queue lengths */
	qs->rbdr_len = RCV_BUF_COUNT;
	qs->sq_len = SND_QUEUE_LEN;
	qs->cq_len = CMP_QUEUE_LEN;

	nic->rx_queues = qs->rq_cnt;
	nic->tx_queues = qs->sq_cnt;

	return (0);
}