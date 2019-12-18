#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* demux; } ;
struct mlx4_ib_dev {TYPE_2__ sriov; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** tun; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pv_object(struct mlx4_ib_dev *dev, int slave, int port)
{
	if (dev->sriov.demux[port - 1].tun[slave]) {
		kfree(dev->sriov.demux[port - 1].tun[slave]);
		dev->sriov.demux[port - 1].tun[slave] = NULL;
	}
}