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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct ethtool_modinfo {void* eeprom_len; void* type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 void* ETH_MODULE_SFF_8436 ; 
 void* ETH_MODULE_SFF_8436_LEN ; 
 void* ETH_MODULE_SFF_8472 ; 
 void* ETH_MODULE_SFF_8472_LEN ; 
 void* ETH_MODULE_SFF_8636 ; 
 void* ETH_MODULE_SFF_8636_LEN ; 
#define  MLX4_MODULE_ID_QSFP 131 
#define  MLX4_MODULE_ID_QSFP28 130 
#define  MLX4_MODULE_ID_QSFP_PLUS 129 
#define  MLX4_MODULE_ID_SFP 128 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int mlx4_get_module_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_module_info(struct net_device *dev,
				   struct ethtool_modinfo *modinfo)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int ret;
	u8 data[4];

	/* Read first 2 bytes to get Module & REV ID */
	ret = mlx4_get_module_info(mdev->dev, priv->port,
				   0/*offset*/, 2/*size*/, data);

	if (ret < 2) {
		en_err(priv, "Failed to read eeprom module first two bytes, error: 0x%x\n", -ret);
		return -EIO;
	}

	switch (data[0] /* identifier */) {
	case MLX4_MODULE_ID_QSFP:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		break;
	case MLX4_MODULE_ID_QSFP_PLUS:
		if (data[1] >= 0x3) { /* revision id */
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		} else {
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		}
		break;
	case MLX4_MODULE_ID_QSFP28:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		break;
	case MLX4_MODULE_ID_SFP:
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		break;
	default:
		en_err(priv, "mlx4_en_get_module_info :  Not recognized cable type\n");
		return -EINVAL;
	}

	return 0;
}