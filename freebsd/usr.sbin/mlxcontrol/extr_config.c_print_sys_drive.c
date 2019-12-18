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
struct mlx_sys_drv {int sd_raidlevel; int sd_valid_spans; int /*<<< orphan*/  sd_valid_arms; int /*<<< orphan*/ * sd_span; } ;
struct TYPE_2__ {struct mlx_sys_drv* cc_sys_drives; } ;
struct conf_config {TYPE_1__ cc_cfg; } ;

/* Variables and functions */
#define  MLX_SYS_DRV_JBOD 133 
#define  MLX_SYS_DRV_RAID0 132 
#define  MLX_SYS_DRV_RAID1 131 
#define  MLX_SYS_DRV_RAID3 130 
#define  MLX_SYS_DRV_RAID5 129 
#define  MLX_SYS_DRV_RAID6 128 
 int MLX_SYS_DRV_WRITEBACK ; 
 int /*<<< orphan*/  print_span (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_sys_drive(struct conf_config *conf, int drvno)
{
    struct mlx_sys_drv	*drv = &conf->cc_cfg.cc_sys_drives[drvno];
    int			i;

    printf("drive%02d ", drvno);
    switch(drv->sd_raidlevel & 0xf) {
    case MLX_SYS_DRV_RAID0:
	printf("RAID0");
	break;
    case MLX_SYS_DRV_RAID1:
	printf("RAID1");
	break;
    case MLX_SYS_DRV_RAID3:
	printf("RAID3");
	break;
    case MLX_SYS_DRV_RAID5:
	printf("RAID5");
	break;
    case MLX_SYS_DRV_RAID6:
	printf("RAID6");
	break;
    case MLX_SYS_DRV_JBOD:
	printf("JBOD");
	break;
    default:
	printf("RAID?");
    }
    printf(" write%s\n", drv->sd_raidlevel & MLX_SYS_DRV_WRITEBACK ? "back" : "through");
    
    for (i = 0; i < drv->sd_valid_spans; i++) {
	printf("  span%d ", i);
	print_span(&drv->sd_span[i], drv->sd_valid_arms);
    }
}