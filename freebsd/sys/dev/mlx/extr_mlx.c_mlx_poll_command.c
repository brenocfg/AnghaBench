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
struct mlx_softc {int /*<<< orphan*/  mlx_dev; int /*<<< orphan*/  mlx_work; } ;
struct mlx_command {scalar_t__ mc_status; struct mlx_softc* mc_sc; int /*<<< orphan*/ * mc_private; int /*<<< orphan*/ * mc_complete; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 scalar_t__ MLX_STATUS_BUSY ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_link ; 
 int /*<<< orphan*/  mlx_diagnose_command (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_done (struct mlx_softc*,int) ; 
 int mlx_start (struct mlx_command*) ; 

__attribute__((used)) static int
mlx_poll_command(struct mlx_command *mc)
{
    struct mlx_softc	*sc = mc->mc_sc;
    int			error, count;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    mc->mc_complete = NULL;
    mc->mc_private = NULL;	/* we will poll for it */
    if ((error = mlx_start(mc)) != 0)
	return(error);
    
    count = 0;
    do {
	/* poll for completion */
	mlx_done(mc->mc_sc, 1);
	
    } while ((mc->mc_status == MLX_STATUS_BUSY) && (count++ < 15000000));
    if (mc->mc_status != MLX_STATUS_BUSY) {
	TAILQ_REMOVE(&sc->mlx_work, mc, mc_link);
	return(0);
    }
    device_printf(sc->mlx_dev, "command failed - %s\n", mlx_diagnose_command(mc));
    return(EIO);
}