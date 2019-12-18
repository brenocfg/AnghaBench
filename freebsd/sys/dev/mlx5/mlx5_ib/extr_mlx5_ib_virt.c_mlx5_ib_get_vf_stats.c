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
typedef  int /*<<< orphan*/  u8 ;
struct ifla_vf_stats {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int mlx5_ib_get_vf_stats(struct ib_device *device, int vf,
			 u8 port, struct ifla_vf_stats *stats)
{
	return -EOPNOTSUPP;
}