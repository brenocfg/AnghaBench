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
struct net_device {scalar_t__ if_type; int /*<<< orphan*/ * if_softc; int /*<<< orphan*/ * if_dname; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IFT_ETHER ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool mlx5_netdev_match(struct net_device *ndev,
			      struct mlx5_core_dev *mdev,
			      const char *dname)
{
	return ndev->if_type == IFT_ETHER &&
	  ndev->if_dname != NULL &&
	  strcmp(ndev->if_dname, dname) == 0 &&
	  ndev->if_softc != NULL &&
	  *(struct mlx5_core_dev **)ndev->if_softc == mdev;
}