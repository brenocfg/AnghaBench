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
struct mlx_sysdrive {scalar_t__ ms_disk; int ms_size; int ms_raidlevel; int ms_heads; int ms_sectors; int ms_cylinders; int /*<<< orphan*/  ms_state; } ;
struct mlx_softc {scalar_t__ mlx_geom; int /*<<< orphan*/  (* mlx_intaction ) (struct mlx_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mlx_state; int /*<<< orphan*/  mlx_dev; struct mlx_sysdrive* mlx_sysdrive; } ;
struct mlx_enq_sys_drive {int sd_size; int sd_raidlevel; int /*<<< orphan*/  sd_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_ENQSYSDRIVE ; 
 int /*<<< orphan*/  MLX_CONFIG_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_CONFIG_UNLOCK (struct mlx_softc*) ; 
 scalar_t__ MLX_GEOM_128_32 ; 
 int /*<<< orphan*/  MLX_INTACTION_ENABLE ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int MLX_MAXDRIVES ; 
 int /*<<< orphan*/  MLX_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (scalar_t__,struct mlx_sysdrive*) ; 
 int /*<<< orphan*/  free (struct mlx_enq_sys_drive*,int /*<<< orphan*/ ) ; 
 struct mlx_enq_sys_drive* mlx_enquire (struct mlx_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx_softc*,int /*<<< orphan*/ ) ; 

void
mlx_startup(struct mlx_softc *sc)
{
    struct mlx_enq_sys_drive	*mes;
    struct mlx_sysdrive		*dr;
    int				i, error;

    debug_called(1);
    
    /*
     * Scan all the system drives and attach children for those that
     * don't currently have them.
     */
    MLX_IO_LOCK(sc);
    mes = mlx_enquire(sc, MLX_CMD_ENQSYSDRIVE, sizeof(*mes) * MLX_MAXDRIVES, NULL);
    MLX_IO_UNLOCK(sc);
    if (mes == NULL) {
	device_printf(sc->mlx_dev, "error fetching drive status\n");
	return;
    }
    
    /* iterate over drives returned */
    MLX_CONFIG_LOCK(sc);
    for (i = 0, dr = &sc->mlx_sysdrive[0];
	 (i < MLX_MAXDRIVES) && (mes[i].sd_size != 0xffffffff);
	 i++, dr++) {
	/* are we already attached to this drive? */
    	if (dr->ms_disk == 0) {
	    /* pick up drive information */
	    dr->ms_size = mes[i].sd_size;
	    dr->ms_raidlevel = mes[i].sd_raidlevel & 0xf;
	    dr->ms_state = mes[i].sd_state;

	    /* generate geometry information */
	    if (sc->mlx_geom == MLX_GEOM_128_32) {
		dr->ms_heads = 128;
		dr->ms_sectors = 32;
		dr->ms_cylinders = dr->ms_size / (128 * 32);
	    } else {        /* MLX_GEOM_255/63 */
		dr->ms_heads = 255;
		dr->ms_sectors = 63;
		dr->ms_cylinders = dr->ms_size / (255 * 63);
	    }
	    dr->ms_disk =  device_add_child(sc->mlx_dev, /*"mlxd"*/NULL, -1);
	    if (dr->ms_disk == 0)
		device_printf(sc->mlx_dev, "device_add_child failed\n");
	    device_set_ivars(dr->ms_disk, dr);
	}
    }
    free(mes, M_DEVBUF);
    if ((error = bus_generic_attach(sc->mlx_dev)) != 0)
	device_printf(sc->mlx_dev, "bus_generic_attach returned %d", error);

    /* mark controller back up */
    MLX_IO_LOCK(sc);
    sc->mlx_state &= ~MLX_STATE_SHUTDOWN;

    /* enable interrupts */
    sc->mlx_intaction(sc, MLX_INTACTION_ENABLE);
    MLX_IO_UNLOCK(sc);
    MLX_CONFIG_UNLOCK(sc);
}