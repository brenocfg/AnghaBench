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
struct mlx_rebuild_status {int /*<<< orphan*/  rs_code; } ;
struct mlx_softc {int mlx_background; struct mlx_rebuild_status mlx_rebuildstat; int /*<<< orphan*/  mlx_dev; } ;
struct mlx_command {int mc_status; scalar_t__ mc_data; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
#define  MLX_BACKGROUND_CHECK 130 
#define  MLX_BACKGROUND_REBUILD 129 
#define  MLX_BACKGROUND_SPONTANEOUS 128 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_REBUILDSTAT_IDLE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 

__attribute__((used)) static void
mlx_periodic_rebuild(struct mlx_command *mc)
{
    struct mlx_softc		*sc = mc->mc_sc;
    struct mlx_rebuild_status	*mr = (struct mlx_rebuild_status *)mc->mc_data;

    MLX_IO_ASSERT_LOCKED(sc);
    switch(mc->mc_status) {
    case 0:				/* operation running, update stats */
	sc->mlx_rebuildstat = *mr;

	/* spontaneous rebuild/check? */
	if (sc->mlx_background == 0) {
	    sc->mlx_background = MLX_BACKGROUND_SPONTANEOUS;
	    device_printf(sc->mlx_dev, "background check/rebuild operation started\n");
	}
	break;

    case 0x0105:			/* nothing running, finalise stats and report */
	switch(sc->mlx_background) {
	case MLX_BACKGROUND_CHECK:
	    device_printf(sc->mlx_dev, "consistency check completed\n");	/* XXX print drive? */
	    break;
	case MLX_BACKGROUND_REBUILD:
	    device_printf(sc->mlx_dev, "drive rebuild completed\n");	/* XXX print channel/target? */
	    break;
	case MLX_BACKGROUND_SPONTANEOUS:
	default:
	    /* if we have previously been non-idle, report the transition */
	    if (sc->mlx_rebuildstat.rs_code != MLX_REBUILDSTAT_IDLE) {
		device_printf(sc->mlx_dev, "background check/rebuild operation completed\n");
	    }
	}
	sc->mlx_background = 0;
	sc->mlx_rebuildstat.rs_code = MLX_REBUILDSTAT_IDLE;
	break;
    }
    free(mc->mc_data, M_DEVBUF);
    mlx_releasecmd(mc);
}