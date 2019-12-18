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
struct ib_port_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int eth_link_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*,int) ; 
 int ib_link_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*,int) ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_ib_port_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 

int __mlx4_ib_query_port(struct ib_device *ibdev, u8 port,
			 struct ib_port_attr *props, int netw_view)
{
	int err;

	memset(props, 0, sizeof *props);

	err = mlx4_ib_port_link_layer(ibdev, port) == IB_LINK_LAYER_INFINIBAND ?
		ib_link_query_port(ibdev, port, props, netw_view) :
				eth_link_query_port(ibdev, port, props, netw_view);

	return err;
}