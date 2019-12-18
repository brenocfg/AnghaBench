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
struct ibv_qp_1_0 {int /*<<< orphan*/  real_qp; } ;

/* Variables and functions */
 int ibv_detach_mcast (int /*<<< orphan*/ ,union ibv_gid*,int /*<<< orphan*/ ) ; 

int __ibv_detach_mcast_1_0(struct ibv_qp_1_0 *qp, union ibv_gid *gid, uint16_t lid)
{
	return ibv_detach_mcast(qp->real_qp, gid, lid);
}