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
struct mlx_softc {int /*<<< orphan*/  mlx_dev; } ;
struct mlx_command {int mc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_REBUILDASYNC ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_diagnose_command (struct mlx_command*) ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_make_type2 (struct mlx_command*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 scalar_t__ mlx_wait_command (struct mlx_command*) ; 

__attribute__((used)) static int
mlx_rebuild(struct mlx_softc *sc, int channel, int target)
{
    struct mlx_command	*mc;
    int			error;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    /* get ourselves a command buffer */
    error = 0x10000;
    if ((mc = mlx_alloccmd(sc)) == NULL)
	goto out;
    /* get a command slot */
    if (mlx_getslot(mc))
	goto out;

    /* build a checkasync command, set the "fix it" flag */
    mlx_make_type2(mc, MLX_CMD_REBUILDASYNC, channel, target, 0, 0, 0, 0, 0, 0);

    /* start the command and wait for it to be returned */
    if (mlx_wait_command(mc))
	goto out;
    
    /* command completed OK? */
    if (mc->mc_status != 0) {	
	device_printf(sc->mlx_dev, "REBUILD ASYNC failed - %s\n", mlx_diagnose_command(mc));
    } else {
	device_printf(sc->mlx_dev, "drive rebuild started for %d:%d\n", channel, target);
    }
    error = mc->mc_status;

 out:
    if (mc != NULL)
	mlx_releasecmd(mc);
    return(error);
}