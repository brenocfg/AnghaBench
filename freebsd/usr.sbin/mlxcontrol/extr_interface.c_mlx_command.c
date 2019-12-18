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
struct mlx_usercommand {int mu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_COMMAND ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mlx_usercommand*) ; 

void
mlx_command(int fd, void *arg)
{
    struct mlx_usercommand	*cmd = (struct mlx_usercommand *)arg;
    int				error;
    
    error = ioctl(fd, MLX_COMMAND, cmd);
    if (error != 0)
	cmd->mu_error = error;
}