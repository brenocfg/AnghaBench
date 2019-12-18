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
typedef  int /*<<< orphan*/  uint8_t ;
struct ibv_query_port {int dummy; } ;
struct ibv_port_attr {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int ibv_cmd_query_port (struct ibv_context*,int /*<<< orphan*/ ,struct ibv_port_attr*,struct ibv_query_port*,int) ; 

int mlx5_query_port(struct ibv_context *context, uint8_t port,
		     struct ibv_port_attr *attr)
{
	struct ibv_query_port cmd;

	return ibv_cmd_query_port(context, port, attr, &cmd, sizeof cmd);
}