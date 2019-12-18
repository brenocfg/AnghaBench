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
typedef  int u32 ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_qp_context {int /*<<< orphan*/  qkey; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ mlx4_get_parav_qkey (struct mlx4_dev*,int,int*) ; 

__attribute__((used)) static void adjust_proxy_tun_qkey(struct mlx4_dev *dev, struct mlx4_vhcr *vhcr,
				  struct mlx4_qp_context *context)
{
	u32 qpn = vhcr->in_modifier & 0xffffff;
	u32 qkey = 0;

	if (mlx4_get_parav_qkey(dev, qpn, &qkey))
		return;

	/* adjust qkey in qp context */
	context->qkey = cpu_to_be32(qkey);
}