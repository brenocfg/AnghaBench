#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_ports; int* qp0_proxy; int /*<<< orphan*/ * qp0_qkey; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */

__attribute__((used)) static int qp0_enabled_vf(struct mlx4_dev *dev, int qpn)
{
	int i;
	for (i = 0; i < dev->caps.num_ports; i++) {
		if (qpn == dev->caps.qp0_proxy[i])
			return !!dev->caps.qp0_qkey[i];
	}
	return 0;
}