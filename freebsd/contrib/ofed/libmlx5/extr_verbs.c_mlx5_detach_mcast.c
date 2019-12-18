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

/* Variables and functions */
 int ibv_cmd_detach_mcast (struct ibv_qp*,union ibv_gid const*,int /*<<< orphan*/ ) ; 

int mlx5_detach_mcast(struct ibv_qp *qp, const union ibv_gid *gid, uint16_t lid)
{
	return ibv_cmd_detach_mcast(qp, gid, lid);
}