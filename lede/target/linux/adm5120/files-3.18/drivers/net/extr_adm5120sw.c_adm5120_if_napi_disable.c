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
struct adm5120_if_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct adm5120_if_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void adm5120_if_napi_disable(struct net_device *dev)
{
	struct adm5120_if_priv *priv = netdev_priv(dev);
	napi_disable(&priv->napi);
}