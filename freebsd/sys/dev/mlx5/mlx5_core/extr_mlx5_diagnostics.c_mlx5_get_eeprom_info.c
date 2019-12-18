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
typedef  int u32 ;
struct mlx5_eeprom {int page_valid; void* len; void* type; int /*<<< orphan*/  module_num; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  page_num; int /*<<< orphan*/  i2c_addr; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_EEPROM_IDENTIFIER_BYTE_MASK ; 
 int /*<<< orphan*/  MLX5_EEPROM_INFO_BYTES ; 
 int MLX5_EEPROM_PAGE_3_VALID_BIT_MASK ; 
 int MLX5_EEPROM_REVISION_ID_BYTE_MASK ; 
 void* MLX5_ETH_MODULE_SFF_8436 ; 
 void* MLX5_ETH_MODULE_SFF_8436_LEN ; 
 void* MLX5_ETH_MODULE_SFF_8472 ; 
 void* MLX5_ETH_MODULE_SFF_8472_LEN ; 
 void* MLX5_ETH_MODULE_SFF_8636 ; 
 void* MLX5_ETH_MODULE_SFF_8636_LEN ; 
#define  SFF_8024_ID_QSFP 131 
#define  SFF_8024_ID_QSFP28 130 
#define  SFF_8024_ID_QSFPPLUS 129 
#define  SFF_8024_ID_SFP 128 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int,...) ; 
 int mlx5_query_eeprom (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int mlx5_query_module_num (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sff_8024_id ; 

int
mlx5_get_eeprom_info(struct mlx5_core_dev *dev, struct mlx5_eeprom *eeprom)
{
	u32 data = 0;
	int size_read = 0;
	int ret;

	ret = mlx5_query_module_num(dev, &eeprom->module_num);
	if (ret) {
		mlx5_core_err(dev, "Failed query module error=%d\n", ret);
		return (-ret);
	}

	/* Read the first three bytes to get Identifier, Revision and Status */
	ret = mlx5_query_eeprom(dev, eeprom->i2c_addr, eeprom->page_num,
	    eeprom->device_addr, MLX5_EEPROM_INFO_BYTES, eeprom->module_num, &data,
	    &size_read);
	if (ret) {
		mlx5_core_err(dev,
		    "Failed query EEPROM module error=0x%x\n", ret);
		return (-ret);
	}

	switch (data & MLX5_EEPROM_IDENTIFIER_BYTE_MASK) {
	case SFF_8024_ID_QSFP:
		eeprom->type = MLX5_ETH_MODULE_SFF_8436;
		eeprom->len = MLX5_ETH_MODULE_SFF_8436_LEN;
		break;
	case SFF_8024_ID_QSFPPLUS:
	case SFF_8024_ID_QSFP28:
		if ((data & MLX5_EEPROM_IDENTIFIER_BYTE_MASK) == SFF_8024_ID_QSFP28 ||
		    ((data & MLX5_EEPROM_REVISION_ID_BYTE_MASK) >> 8) >= 0x3) {
			eeprom->type = MLX5_ETH_MODULE_SFF_8636;
			eeprom->len = MLX5_ETH_MODULE_SFF_8636_LEN;
		} else {
			eeprom->type = MLX5_ETH_MODULE_SFF_8436;
			eeprom->len = MLX5_ETH_MODULE_SFF_8436_LEN;
		}
		if ((data & MLX5_EEPROM_PAGE_3_VALID_BIT_MASK) == 0)
			eeprom->page_valid = 1;
		break;
	case SFF_8024_ID_SFP:
		eeprom->type = MLX5_ETH_MODULE_SFF_8472;
		eeprom->len = MLX5_ETH_MODULE_SFF_8472_LEN;
		break;
	default:
		mlx5_core_err(dev, "Not recognized cable type = 0x%x(%s)\n",
		    data & MLX5_EEPROM_IDENTIFIER_BYTE_MASK,
		    sff_8024_id[data & MLX5_EEPROM_IDENTIFIER_BYTE_MASK]);
		return (EINVAL);
	}
	return (0);
}