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
struct mlx_softc {int mlx_flags; int /*<<< orphan*/  mlx_dev; } ;

/* Variables and functions */
 int MLX_SPINUP_REPORTED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
mlx_fw_message(struct mlx_softc *sc, int error, int param1, int param2)
{
    switch(error) {
    case 0x00:
	device_printf(sc->mlx_dev, "physical drive %d:%d not responding\n", param2, param1);
	break;
    case 0x08:
	/* we could be neater about this and give some indication when we receive more of them */
	if (!(sc->mlx_flags & MLX_SPINUP_REPORTED)) {
	    device_printf(sc->mlx_dev, "spinning up drives...\n");
	    sc->mlx_flags |= MLX_SPINUP_REPORTED;
	}
	break;
    case 0x30:
	device_printf(sc->mlx_dev, "configuration checksum error\n");
	break;
    case 0x60:
	device_printf(sc->mlx_dev, "mirror race recovery failed\n");
	break;
    case 0x70:
	device_printf(sc->mlx_dev, "mirror race recovery in progress\n");
	break;
    case 0x90:
	device_printf(sc->mlx_dev, "physical drive %d:%d COD mismatch\n", param2, param1);
	break;
    case 0xa0:
	device_printf(sc->mlx_dev, "logical drive installation aborted\n");
	break;
    case 0xb0:
	device_printf(sc->mlx_dev, "mirror race on a critical system drive\n");
	break;
    case 0xd0:
	device_printf(sc->mlx_dev, "new controller configuration found\n");
	break;
    case 0xf0:
	device_printf(sc->mlx_dev, "FATAL MEMORY PARITY ERROR\n");
	return(1);
    default:
	device_printf(sc->mlx_dev, "unknown firmware initialisation error %02x:%02x:%02x\n", error, param1, param2);
	break;
    }
    return(0);
}