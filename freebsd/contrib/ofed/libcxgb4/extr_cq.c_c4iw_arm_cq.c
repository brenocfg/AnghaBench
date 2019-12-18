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
struct ibv_cq {int dummy; } ;
struct c4iw_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INC_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_arm_cq (int /*<<< orphan*/ *,int) ; 
 struct c4iw_cq* to_c4iw_cq (struct ibv_cq*) ; 

int c4iw_arm_cq(struct ibv_cq *ibcq, int solicited)
{
	struct c4iw_cq *chp;
	int ret;

	INC_STAT(arm);
	chp = to_c4iw_cq(ibcq);
	pthread_spin_lock(&chp->lock);
	ret = t4_arm_cq(&chp->cq, solicited);
	pthread_spin_unlock(&chp->lock);
	return ret;
}