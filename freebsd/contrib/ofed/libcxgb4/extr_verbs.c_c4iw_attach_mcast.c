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
typedef  union ibv_gid {int dummy; } ibv_gid ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ibv_qp {int dummy; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_flush_qp (struct c4iw_qp*) ; 
 int ibv_cmd_attach_mcast (struct ibv_qp*,union ibv_gid const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ t4_wq_in_error (int /*<<< orphan*/ *) ; 
 struct c4iw_qp* to_c4iw_qp (struct ibv_qp*) ; 

int c4iw_attach_mcast(struct ibv_qp *ibqp, const union ibv_gid *gid,
		      uint16_t lid)
{
	struct c4iw_qp *qhp = to_c4iw_qp(ibqp);
	int ret;

	pthread_spin_lock(&qhp->lock);
	if (t4_wq_in_error(&qhp->wq))
		c4iw_flush_qp(qhp);
	ret = ibv_cmd_attach_mcast(ibqp, gid, lid);
	pthread_spin_unlock(&qhp->lock);
	return ret;
}