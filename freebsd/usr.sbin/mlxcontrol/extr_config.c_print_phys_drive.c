#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx_phys_drv {int pd_flags1; } ;
struct TYPE_2__ {struct mlx_phys_drv* cc_phys_drives; } ;
struct conf_config {TYPE_1__ cc_cfg; } ;

/* Variables and functions */
 int MLX_PHYS_DRV_PRESENT ; 
 int /*<<< orphan*/  mlx_print_phys_drv (struct mlx_phys_drv*,int,int,char*,int) ; 

__attribute__((used)) static void
print_phys_drive(struct conf_config *conf, int chn, int targ)
{
    struct mlx_phys_drv		*drv = &conf->cc_cfg.cc_phys_drives[chn * 16 + targ];
 
    /* if the drive isn't present, don't print it */
    if (!(drv->pd_flags1 & MLX_PHYS_DRV_PRESENT))
	return;

    mlx_print_phys_drv(drv, chn, targ, "# ", 1);
}