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
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct mlx5e_eth_addr_hash_node {TYPE_1__ ai; } ;
struct mlx5e_copy_addr_ctx {int success; int /*<<< orphan*/  fill; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_eth_addr_hash_node* mlx5e_move_hn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
mlx5e_copy_addr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct mlx5e_copy_addr_ctx *ctx = arg;
	struct mlx5e_eth_addr_hash_node *hn;

	hn = mlx5e_move_hn(ctx->free, ctx->fill);
	if (hn == NULL) {
		ctx->success = false;
		return (0);
	}
	ether_addr_copy(hn->ai.addr, LLADDR(sdl));

	return (1);
}