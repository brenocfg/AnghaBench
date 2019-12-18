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

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FW_RESET ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mlx5_tool_addr const*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
mlx5tool_fw_reset(int ctldev, const struct mlx5_tool_addr *addr)
{

	if (ioctl(ctldev, MLX5_FW_RESET, addr) == -1) {
		warn("MLX5_FW_RESET");
		return (1);
	}
	return (0);
}