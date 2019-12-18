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
struct mlx5e_eth_addr_hash_node {int dummy; } ;
struct mlx5e_eth_addr_hash_head {int dummy; } ;

/* Variables and functions */
 struct mlx5e_eth_addr_hash_node* LIST_FIRST (struct mlx5e_eth_addr_hash_head*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct mlx5e_eth_addr_hash_head*,struct mlx5e_eth_addr_hash_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct mlx5e_eth_addr_hash_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist ; 

__attribute__((used)) static struct mlx5e_eth_addr_hash_node *
mlx5e_move_hn(struct mlx5e_eth_addr_hash_head *fh, struct mlx5e_eth_addr_hash_head *uh)
{
	struct mlx5e_eth_addr_hash_node *hn;

	hn = LIST_FIRST(fh);
	if (hn != NULL) {
		LIST_REMOVE(hn, hlist);
		LIST_INSERT_HEAD(uh, hn, hlist);
	}
	return (hn);
}