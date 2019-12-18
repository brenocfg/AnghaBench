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
struct mlx_command {int /*<<< orphan*/ * mc_data; struct mlx_command* mc_private; int /*<<< orphan*/  mc_complete; int /*<<< orphan*/  mc_dataphys; TYPE_1__* mc_sc; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_2__ {int /*<<< orphan*/  mlx_lastevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_LOGOP ; 
 int /*<<< orphan*/  MLX_LOGOP_GET ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_make_type3 (struct mlx_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_periodic_eventlog_respond ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_setup_dmamap (struct mlx_command*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ mlx_start (struct mlx_command*) ; 

__attribute__((used)) static void
mlx_eventlog_cb(void *arg, bus_dma_segment_t *segs, int nsegments, int error)
{
    struct mlx_command *mc;

    mc = (struct mlx_command *)arg;
    mlx_setup_dmamap(mc, segs, nsegments, error);

    /* build the command to get one entry */
    mlx_make_type3(mc, MLX_CMD_LOGOP, MLX_LOGOP_GET, 1,
		   mc->mc_sc->mlx_lastevent, 0, 0, mc->mc_dataphys, 0);
    mc->mc_complete = mlx_periodic_eventlog_respond;
    mc->mc_private = mc;

    /* start the command */
    if (mlx_start(mc) != 0) {
	mlx_releasecmd(mc);
	free(mc->mc_data, M_DEVBUF);
	mc->mc_data = NULL;
    }
    
}