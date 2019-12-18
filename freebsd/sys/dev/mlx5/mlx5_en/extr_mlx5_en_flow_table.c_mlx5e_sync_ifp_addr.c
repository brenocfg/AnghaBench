#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_dl {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  if_mc; int /*<<< orphan*/  if_uc; } ;
struct mlx5e_priv {TYPE_3__ eth_addr; int /*<<< orphan*/  mdev; struct ifnet* ifp; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct mlx5e_eth_addr_hash_node {unsigned int mpfs_index; TYPE_2__ ai; int /*<<< orphan*/  action; } ;
struct mlx5e_eth_addr_hash_head {int dummy; } ;
struct mlx5e_copy_addr_ctx {int success; struct mlx5e_eth_addr_hash_head* fill; struct mlx5e_eth_addr_hash_head* free; } ;
struct ifnet {TYPE_1__* if_addr; } ;
struct TYPE_4__ {scalar_t__ ifa_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (struct mlx5e_eth_addr_hash_head*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct mlx5e_eth_addr_hash_head*,struct mlx5e_eth_addr_hash_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  MLX5E_ACTION_ADD ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MLX5EN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIV_ASSERT_LOCKED (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mlx5e_eth_addr_hash_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist ; 
 int /*<<< orphan*/  if_foreach_lladdr (struct ifnet*,int /*<<< orphan*/ ,struct mlx5e_copy_addr_ctx*) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct mlx5e_copy_addr_ctx*) ; 
 int if_lladdr_count (struct ifnet*) ; 
 int if_llmaddr_count (struct ifnet*) ; 
 struct mlx5e_eth_addr_hash_node* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_mpfs_add_mac (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_add_eth_addr_to_hash (int /*<<< orphan*/ ,struct mlx5e_eth_addr_hash_node*) ; 
 int /*<<< orphan*/  mlx5e_copy_addr ; 
 struct mlx5e_eth_addr_hash_node* mlx5e_move_hn (struct mlx5e_eth_addr_hash_head*,struct mlx5e_eth_addr_hash_head*) ; 
 struct mlx5e_eth_addr_hash_node* mlx5e_remove_hn (struct mlx5e_eth_addr_hash_head*) ; 

__attribute__((used)) static void
mlx5e_sync_ifp_addr(struct mlx5e_priv *priv)
{
	struct mlx5e_copy_addr_ctx ctx;
	struct mlx5e_eth_addr_hash_head head_free;
	struct mlx5e_eth_addr_hash_head head_uc;
	struct mlx5e_eth_addr_hash_head head_mc;
	struct mlx5e_eth_addr_hash_node *hn;
	struct ifnet *ifp = priv->ifp;
	size_t x;
	size_t num;

	PRIV_ASSERT_LOCKED(priv);

retry:
	LIST_INIT(&head_free);
	LIST_INIT(&head_uc);
	LIST_INIT(&head_mc);
	num = 1 + if_lladdr_count(ifp) + if_llmaddr_count(ifp);

	/* allocate place holders */
	for (x = 0; x != num; x++) {
		hn = malloc(sizeof(*hn), M_MLX5EN, M_WAITOK | M_ZERO);
		hn->action = MLX5E_ACTION_ADD;
		hn->mpfs_index = -1U;
		LIST_INSERT_HEAD(&head_free, hn, hlist);
	}

	hn = mlx5e_move_hn(&head_free, &head_uc);
	MPASS(hn != NULL);

	ether_addr_copy(hn->ai.addr,
	    LLADDR((struct sockaddr_dl *)(ifp->if_addr->ifa_addr)));

	ctx.free = &head_free;
	ctx.fill = &head_uc;
	ctx.success = true;
	if_foreach_lladdr(ifp, mlx5e_copy_addr, &ctx);
	if (ctx.success == false)
		goto cleanup;

	ctx.fill = &head_mc;
	if_foreach_llmaddr(ifp, mlx5e_copy_addr, &ctx);
	if (ctx.success == false)
		goto cleanup;

	/* insert L2 unicast addresses into hash list */

	while ((hn = mlx5e_remove_hn(&head_uc)) != NULL) {
		if (mlx5e_add_eth_addr_to_hash(priv->eth_addr.if_uc, hn) == 0)
			continue;
		if (hn->mpfs_index == -1U)
			mlx5_mpfs_add_mac(priv->mdev, &hn->mpfs_index, hn->ai.addr);
	}

	/* insert L2 multicast addresses into hash list */

	while ((hn = mlx5e_remove_hn(&head_mc)) != NULL) {
		if (mlx5e_add_eth_addr_to_hash(priv->eth_addr.if_mc, hn) == 0)
			continue;
	}

cleanup:
	while ((hn = mlx5e_remove_hn(&head_uc)) != NULL)
		free(hn, M_MLX5EN);
	while ((hn = mlx5e_remove_hn(&head_mc)) != NULL)
		free(hn, M_MLX5EN);
	while ((hn = mlx5e_remove_hn(&head_free)) != NULL)
		free(hn, M_MLX5EN);

	if (ctx.success == false)
		goto retry;
}