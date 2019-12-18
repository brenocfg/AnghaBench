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
struct mlx_usercommand {int mu_datasize; int mu_bufptr; scalar_t__ mu_status; int /*<<< orphan*/ * mu_command; struct mlx_enquiry2* mu_buf; } ;
struct mlx_enquiry2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_ENQUIRY2 ; 
 int /*<<< orphan*/  mlx_command ; 
 int /*<<< orphan*/  mlx_perform (int,int /*<<< orphan*/ ,void*) ; 

int
mlx_enquiry(int unit, struct mlx_enquiry2 *enq)
{
    struct mlx_usercommand	cmd;

    /* build the command */
    cmd.mu_datasize = sizeof(*enq);
    cmd.mu_buf = enq;
    cmd.mu_bufptr = 8;
    cmd.mu_command[0] = MLX_CMD_ENQUIRY2;

    /* hand it off for processing */
    mlx_perform(unit, mlx_command, (void *)&cmd);

    return(cmd.mu_status != 0);
}