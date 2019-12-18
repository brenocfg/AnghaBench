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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct mlxd_softc {int /*<<< orphan*/  mlxd_drive; int /*<<< orphan*/  mlxd_controller; } ;
struct disk {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int ENOIOCTL ; 
 int ENOTTY ; 
 int ENXIO ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int mlx_submit_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,struct thread*) ; 

__attribute__((used)) static int
mlxd_ioctl(struct disk *dp, u_long cmd, void *addr, int flag, struct thread *td)
{
    struct mlxd_softc	*sc = (struct mlxd_softc *)dp->d_drv1;
    int error;

    debug_called(1);
	
    if (sc == NULL)
	return (ENXIO);

    if ((error = mlx_submit_ioctl(sc->mlxd_controller, sc->mlxd_drive, cmd, addr, flag, td)) != ENOIOCTL) {
	debug(0, "mlx_submit_ioctl returned %d\n", error);
	return(error);
    }
    return (ENOTTY);
}