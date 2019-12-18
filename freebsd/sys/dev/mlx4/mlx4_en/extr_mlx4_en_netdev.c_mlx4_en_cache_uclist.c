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
struct net_device {int dummy; } ;
struct mlx4_en_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_foreach_lladdr (struct net_device*,int /*<<< orphan*/ ,struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_copy_addr ; 
 int /*<<< orphan*/  mlx4_en_clear_uclist (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_cache_uclist(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	mlx4_en_clear_uclist(dev);
	if_foreach_lladdr(dev, mlx4_copy_addr, priv);
}