#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_24__ ;
typedef  struct TYPE_39__   TYPE_23__ ;
typedef  struct TYPE_38__   TYPE_22__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_27__ {void* packets; void* octets; } ;
struct TYPE_26__ {void* packets; void* octets; } ;
struct TYPE_25__ {void* packets; void* octets; } ;
struct TYPE_48__ {void* packets; void* octets; } ;
struct TYPE_47__ {void* octets; void* packets; } ;
struct TYPE_46__ {void* octets; void* packets; } ;
struct TYPE_45__ {void* octets; void* packets; } ;
struct TYPE_44__ {void* octets; void* packets; } ;
struct TYPE_43__ {void* octets; void* packets; } ;
struct TYPE_42__ {void* octets; void* packets; } ;
struct TYPE_41__ {void* octets; void* packets; } ;
struct TYPE_35__ {void* octets; void* packets; } ;
struct mlx5_vport_counters {TYPE_12__ transmitted_eth_multicast; TYPE_11__ received_eth_multicast; TYPE_10__ transmitted_eth_unicast; TYPE_9__ received_eth_unicast; TYPE_8__ transmitted_eth_broadcast; TYPE_7__ received_eth_broadcast; TYPE_6__ transmitted_ib_multicast; TYPE_5__ received_ib_multicast; TYPE_4__ transmitted_ib_unicast; TYPE_3__ received_ib_unicast; TYPE_2__ transmit_errors; TYPE_1__ received_errors; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_40__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_39__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_38__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_37__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_36__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_34__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_33__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_32__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_31__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_30__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_29__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;
struct TYPE_28__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_GET64 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int mlx5_query_vport_counter (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  query_vport_counter_out ; 
 TYPE_24__ received_errors ; 
 TYPE_23__ received_eth_broadcast ; 
 TYPE_22__ received_eth_multicast ; 
 TYPE_21__ received_eth_unicast ; 
 TYPE_20__ received_ib_multicast ; 
 TYPE_19__ received_ib_unicast ; 
 TYPE_18__ transmit_errors ; 
 TYPE_17__ transmitted_eth_broadcast ; 
 TYPE_16__ transmitted_eth_multicast ; 
 TYPE_15__ transmitted_eth_unicast ; 
 TYPE_14__ transmitted_ib_multicast ; 
 TYPE_13__ transmitted_ib_unicast ; 

int mlx5_get_vport_counters(struct mlx5_core_dev *dev, u8 port_num,
			    struct mlx5_vport_counters *vc)
{
	int out_sz = MLX5_ST_SZ_BYTES(query_vport_counter_out);
	void *out;
	int err;

	out = mlx5_vzalloc(out_sz);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_vport_counter(dev, port_num, 0, out, out_sz);
	if (err)
		goto ex;

	vc->received_errors.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_errors.packets);
	vc->received_errors.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_errors.octets);
	vc->transmit_errors.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmit_errors.packets);
	vc->transmit_errors.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmit_errors.octets);
	vc->received_ib_unicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_ib_unicast.packets);
	vc->received_ib_unicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_ib_unicast.octets);
	vc->transmitted_ib_unicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_ib_unicast.packets);
	vc->transmitted_ib_unicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_ib_unicast.octets);
	vc->received_ib_multicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_ib_multicast.packets);
	vc->received_ib_multicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_ib_multicast.octets);
	vc->transmitted_ib_multicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_ib_multicast.packets);
	vc->transmitted_ib_multicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_ib_multicast.octets);
	vc->received_eth_broadcast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_broadcast.packets);
	vc->received_eth_broadcast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_broadcast.octets);
	vc->transmitted_eth_broadcast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_broadcast.packets);
	vc->transmitted_eth_broadcast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_broadcast.octets);
	vc->received_eth_unicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_unicast.octets);
	vc->received_eth_unicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_unicast.packets);
	vc->transmitted_eth_unicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_unicast.octets);
	vc->transmitted_eth_unicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_unicast.packets);
	vc->received_eth_multicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_multicast.octets);
	vc->received_eth_multicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, received_eth_multicast.packets);
	vc->transmitted_eth_multicast.octets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_multicast.octets);
	vc->transmitted_eth_multicast.packets =
		MLX5_GET64(query_vport_counter_out,
			   out, transmitted_eth_multicast.packets);

ex:
	kvfree(out);
	return err;
}