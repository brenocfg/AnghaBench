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
struct mlx4_en_priv {scalar_t__ port_up; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 struct mlx4_en_priv* netdev_priv (struct ifnet*) ; 

void
mlx4_en_qflush(struct ifnet *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	if (priv->port_up == 0)
		return;

	if_qflush(dev);
}