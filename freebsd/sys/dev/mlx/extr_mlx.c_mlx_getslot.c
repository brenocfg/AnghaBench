#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx_softc {int mlx_busycmds; struct mlx_command** mlx_busycmd; TYPE_1__* mlx_enq2; } ;
struct mlx_command {int mc_flags; int mc_slot; struct mlx_softc* mc_sc; } ;
struct TYPE_2__ {int me_max_commands; } ;

/* Variables and functions */
 int EBUSY ; 
 int MLX_CMD_PRIORITY ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  debug (int,char*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlx_getslot(struct mlx_command *mc)
{
    struct mlx_softc	*sc = mc->mc_sc;
    int			slot, limit;

    debug_called(1);

    MLX_IO_ASSERT_LOCKED(sc);

    /* 
     * Enforce slot-usage limit, if we have the required information.
     */
    if (sc->mlx_enq2 != NULL) {
	limit = sc->mlx_enq2->me_max_commands;
    } else {
	limit = 2;
    }
    if (sc->mlx_busycmds >= ((mc->mc_flags & MLX_CMD_PRIORITY) ? limit : limit - 4))
	return(EBUSY);

    /* 
     * Allocate an outstanding command slot 
     *
     * XXX linear search is slow
     */
    for (slot = 0; slot < limit; slot++) {
	debug(2, "try slot %d", slot);
	if (sc->mlx_busycmd[slot] == NULL)
	    break;
    }
    if (slot < limit) {
	sc->mlx_busycmd[slot] = mc;
	sc->mlx_busycmds++;
    }

    /* out of slots? */
    if (slot >= limit)
	return(EBUSY);

    debug(2, "got slot %d", slot);
    mc->mc_slot = slot;
    return(0);
}