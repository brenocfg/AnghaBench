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
struct mlx4_en_priv {scalar_t__ last_link_state; } ;
struct ifnet {struct mlx4_en_priv* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 scalar_t__ MLX4_DEV_EVENT_PORT_DOWN ; 
 int /*<<< orphan*/  mlx4_en_calc_media (struct mlx4_en_priv*) ; 

__attribute__((used)) static void mlx4_en_media_status(struct ifnet *dev, struct ifmediareq *ifmr)
{
	struct mlx4_en_priv *priv;

	priv = dev->if_softc;
	ifmr->ifm_status = IFM_AVALID;
	if (priv->last_link_state != MLX4_DEV_EVENT_PORT_DOWN)
		ifmr->ifm_status |= IFM_ACTIVE;
	ifmr->ifm_active = mlx4_en_calc_media(priv);

	return;
}