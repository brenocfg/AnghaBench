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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_WOL_ARP ; 
 int /*<<< orphan*/  MLX5_WOL_BROADCAST ; 
 int /*<<< orphan*/  MLX5_WOL_MAGIC ; 
 int /*<<< orphan*/  MLX5_WOL_MULTICAST ; 
 int /*<<< orphan*/  MLX5_WOL_PHY_ACTIVITY ; 
 int /*<<< orphan*/  MLX5_WOL_SECURED_MAGIC ; 
 int /*<<< orphan*/  MLX5_WOL_UNICAST ; 
 int /*<<< orphan*/  wol_a ; 
 int /*<<< orphan*/  wol_b ; 
 int /*<<< orphan*/  wol_g ; 
 int /*<<< orphan*/  wol_m ; 
 int /*<<< orphan*/  wol_p ; 
 int /*<<< orphan*/  wol_s ; 
 int /*<<< orphan*/  wol_u ; 

u8 mlx5_is_wol_supported(struct mlx5_core_dev *dev)
{
	u8 wol_supported = 0;

	if (MLX5_CAP_GEN(dev, wol_s))
		wol_supported |= MLX5_WOL_SECURED_MAGIC;
	if (MLX5_CAP_GEN(dev, wol_g))
		wol_supported |= MLX5_WOL_MAGIC;
	if (MLX5_CAP_GEN(dev, wol_a))
		wol_supported |= MLX5_WOL_ARP;
	if (MLX5_CAP_GEN(dev, wol_b))
		wol_supported |= MLX5_WOL_BROADCAST;
	if (MLX5_CAP_GEN(dev, wol_m))
		wol_supported |= MLX5_WOL_MULTICAST;
	if (MLX5_CAP_GEN(dev, wol_u))
		wol_supported |= MLX5_WOL_UNICAST;
	if (MLX5_CAP_GEN(dev, wol_p))
		wol_supported |= MLX5_WOL_PHY_ACTIVITY;

	return wol_supported;
}