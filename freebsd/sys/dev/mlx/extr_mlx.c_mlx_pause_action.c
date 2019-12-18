#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mp_when; int mp_howlong; int mp_which; } ;
struct mlx_softc {int /*<<< orphan*/  mlx_dev; TYPE_2__ mlx_pause; TYPE_1__* mlx_enq2; } ;
struct mlx_command {struct mlx_softc* mc_private; int /*<<< orphan*/  mc_complete; int /*<<< orphan*/  mc_flags; } ;
struct TYPE_3__ {int me_actual_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_CMD_PRIORITY ; 
 int MLX_CMD_STARTCHANNEL ; 
 int MLX_CMD_STOPCHANNEL ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_make_type2 (struct mlx_command*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx_pause_done ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 scalar_t__ mlx_start (struct mlx_command*) ; 
 int time_second ; 

__attribute__((used)) static void
mlx_pause_action(struct mlx_softc *sc)
{
    struct mlx_command	*mc;
    int			failsafe, i, command;

    MLX_IO_ASSERT_LOCKED(sc);

    /* What are we doing here? */
    if (sc->mlx_pause.mp_when == 0) {
	command = MLX_CMD_STARTCHANNEL;
	failsafe = 0;

    } else {
	command = MLX_CMD_STOPCHANNEL;

	/* 
	 * Channels will always start again after the failsafe period, 
	 * which is specified in multiples of 30 seconds.
	 * This constrains us to a maximum pause of 450 seconds.
	 */
	failsafe = ((sc->mlx_pause.mp_howlong - time_second) + 5) / 30;
	if (failsafe > 0xf) {
	    failsafe = 0xf;
	    sc->mlx_pause.mp_howlong = time_second + (0xf * 30) - 5;
	}
    }

    /* build commands for every channel requested */
    for (i = 0; i < sc->mlx_enq2->me_actual_channels; i++) {
	if ((1 << i) & sc->mlx_pause.mp_which) {

	    /* get ourselves a command buffer */
	    if ((mc = mlx_alloccmd(sc)) == NULL)
		goto fail;
	    /* get a command slot */
	    mc->mc_flags |= MLX_CMD_PRIORITY;
	    if (mlx_getslot(mc))
		goto fail;

	    /* build the command */
	    mlx_make_type2(mc, command, (failsafe << 4) | i, 0, 0, 0, 0, 0, 0, 0);
	    mc->mc_complete = mlx_pause_done;
	    mc->mc_private = sc;		/* XXX not needed */
	    if (mlx_start(mc))
		goto fail;
	    /* command submitted OK */
	    return;
    
	fail:
	    device_printf(sc->mlx_dev, "%s failed for channel %d\n", 
			  command == MLX_CMD_STOPCHANNEL ? "pause" : "resume", i);
	    if (mc != NULL)
		mlx_releasecmd(mc);
	}
    }
}