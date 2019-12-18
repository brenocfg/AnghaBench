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
typedef  int u_long ;
struct thread {int dummy; } ;
struct mlx_sysdrive {int ms_state; } ;
struct mlx_softc {int /*<<< orphan*/  mlx_background; struct mlx_sysdrive* mlx_sysdrive; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOIOCTL ; 
 int ENOMEM ; 
 int ERANGE ; 
#define  MLXD_CHECKASYNC 129 
#define  MLXD_STATUS 128 
 int /*<<< orphan*/  MLX_BACKGROUND_CHECK ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int mlx_check (struct mlx_softc*,int) ; 

int
mlx_submit_ioctl(struct mlx_softc *sc, struct mlx_sysdrive *drive, u_long cmd, 
		caddr_t addr, int32_t flag, struct thread *td)
{
    int				*arg = (int *)addr;
    int				error, result;

    switch(cmd) {
	/*
	 * Return the current status of this drive.
	 */
    case MLXD_STATUS:
	MLX_IO_LOCK(sc);
	*arg = drive->ms_state;
	MLX_IO_UNLOCK(sc);
	return(0);
	
	/*
	 * Start a background consistency check on this drive.
	 */
    case MLXD_CHECKASYNC:		/* start a background consistency check */
	MLX_IO_LOCK(sc);
	if (sc->mlx_background != 0) {
	    MLX_IO_UNLOCK(sc);
	    *arg = 0x0106;
	    return(EBUSY);
	}
	result = mlx_check(sc, drive - &sc->mlx_sysdrive[0]);
	switch (result) {
	case 0:
	    error = 0;
	    break;
	case 0x10000:
	    error = ENOMEM;		/* couldn't set up the command */
	    break;
	case 0x0002:	
	    error = EIO;
	    break;
	case 0x0105:
	    error = ERANGE;
	    break;
	case 0x0106:
	    error = EBUSY;
	    break;
	default:
	    error = EINVAL;
	    break;
	}
	if (error == 0)
	    sc->mlx_background = MLX_BACKGROUND_CHECK;
	MLX_IO_UNLOCK(sc);
	*arg = result;
	return(error);

    }
    return(ENOIOCTL);
}