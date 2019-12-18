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
struct mlx_command {scalar_t__ mc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_FLUSH ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_diagnose_command (struct mlx_command*) ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_make_type2 (struct mlx_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx_poll_command (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 

__attribute__((used)) static int
mlx_flush(struct mlx_softc *sc)
{
    struct mlx_command	*mc;
    int			error;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    /* get ourselves a command buffer */
    error = 1;
    if ((mc = mlx_alloccmd(sc)) == NULL)
	goto out;
    /* get a command slot */
    if (mlx_getslot(mc))
	goto out;

    /* build a flush command */
    mlx_make_type2(mc, MLX_CMD_FLUSH, 0, 0, 0, 0, 0, 0, 0, 0);

    /* can't assume that interrupts are going to work here, so play it safe */
    if (mlx_poll_command(mc))
	goto out;
    
    /* command completed OK? */
    if (mc->mc_status != 0) {
	device_printf(sc->mlx_dev, "FLUSH failed - %s\n", mlx_diagnose_command(mc));
	goto out;
    }
    
    error = 0;			/* success */
 out:
    if (mc != NULL)
	mlx_releasecmd(mc);
    return(error);
}