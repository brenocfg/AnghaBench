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
struct mlx5_tool_addr {int dummy; } ;
struct mlx5_eeprom_get {int /*<<< orphan*/ * eeprom_info_buf; scalar_t__ eeprom_info_out_len; struct mlx5_tool_addr devaddr; } ;
typedef  int /*<<< orphan*/  eeprom_info ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_EEPROM_GET ; 
 scalar_t__ MLX5_EEPROM_PAGE_LENGTH ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mlx5_eeprom_get*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct mlx5_eeprom_get*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5tool_eeprom_print (struct mlx5_eeprom_get*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
mlx5tool_get_eeprom_info(int ctldev, const struct mlx5_tool_addr *addr)
{
	struct mlx5_eeprom_get eeprom_info;
	int error;

	memset(&eeprom_info, 0, sizeof(eeprom_info));
	eeprom_info.devaddr = *addr;

	error = ioctl(ctldev, MLX5_EEPROM_GET, &eeprom_info);
	if (error != 0) {
		warn("MLX5_EEPROM_GET");
		return (error);
	}
	eeprom_info.eeprom_info_buf =
	    malloc(eeprom_info.eeprom_info_out_len + MLX5_EEPROM_PAGE_LENGTH);
	if (eeprom_info.eeprom_info_buf == NULL) {
		warn("alloc eeprom_info.eeprom_info_buf ");
		return (ENOMEM);
	}
	error = ioctl(ctldev, MLX5_EEPROM_GET, &eeprom_info);
	if (error != 0) {
		warn("MLX5_EEPROM_GET");
		free(eeprom_info.eeprom_info_buf);
		return (error);
	}

	mlx5tool_eeprom_print(&eeprom_info);

	free(eeprom_info.eeprom_info_buf);
	return (0);
}