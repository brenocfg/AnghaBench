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
typedef  scalar_t__ uint8_t ;
struct mlx4_context {TYPE_1__* port_query_cache; } ;
struct ibv_query_port {int dummy; } ;
struct ibv_port_attr {int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  link_layer; } ;
struct ibv_context {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int valid; int /*<<< orphan*/  caps; int /*<<< orphan*/  link_layer; } ;

/* Variables and functions */
 scalar_t__ MLX4_PORTS_NUM ; 
 int ibv_cmd_query_port (struct ibv_context*,scalar_t__,struct ibv_port_attr*,struct ibv_query_port*,int) ; 
 struct mlx4_context* to_mctx (struct ibv_context*) ; 

int mlx4_query_port(struct ibv_context *context, uint8_t port,
		     struct ibv_port_attr *attr)
{
	struct ibv_query_port cmd;
	int err;

	err = ibv_cmd_query_port(context, port, attr, &cmd, sizeof(cmd));
	if (!err && port <= MLX4_PORTS_NUM && port > 0) {
		struct mlx4_context *mctx = to_mctx(context);
		if (!mctx->port_query_cache[port - 1].valid) {
			mctx->port_query_cache[port - 1].link_layer =
				attr->link_layer;
			mctx->port_query_cache[port - 1].caps =
				attr->port_cap_flags;
			mctx->port_query_cache[port - 1].valid = 1;
		}
	}

	return err;
}