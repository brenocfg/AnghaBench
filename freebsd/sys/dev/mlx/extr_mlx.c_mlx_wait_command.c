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
struct mlx_softc {int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/  mlx_io_lock; } ;
struct mlx_command {scalar_t__ mc_status; struct mlx_command* mc_private; int /*<<< orphan*/ * mc_complete; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 scalar_t__ MLX_STATUS_BUSY ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mlx_diagnose_command (struct mlx_command*) ; 
 int mlx_start (struct mlx_command*) ; 
 int /*<<< orphan*/  mtx_sleep (struct mlx_command*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx_wait_command(struct mlx_command *mc)
{
    struct mlx_softc	*sc = mc->mc_sc;
    int			error, count;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    mc->mc_complete = NULL;
    mc->mc_private = mc;		/* wake us when you're done */
    if ((error = mlx_start(mc)) != 0)
	return(error);

    count = 0;
    /* XXX better timeout? */
    while ((mc->mc_status == MLX_STATUS_BUSY) && (count < 30)) {
	mtx_sleep(mc->mc_private, &sc->mlx_io_lock, PRIBIO | PCATCH, "mlxwcmd", hz);
    }

    if (mc->mc_status != 0) {
	device_printf(sc->mlx_dev, "command failed - %s\n", mlx_diagnose_command(mc));
	return(EIO);
    }
    return(0);
}