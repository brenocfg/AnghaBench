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
struct mly_softc {int mly_state; int /*<<< orphan*/  mly_lock; } ;
struct mly_command {int mc_flags; struct mly_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLY_ASSERT_LOCKED (struct mly_softc*) ; 
 int MLY_CMD_COMPLETE ; 
 int MLY_STATE_INTERRUPTS_ON ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_done (struct mly_softc*) ; 
 int mly_start (struct mly_command*) ; 
 int /*<<< orphan*/  mtx_sleep (struct mly_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_immediate_command(struct mly_command *mc)
{
    struct mly_softc	*sc = mc->mc_sc;
    int			error;

    debug_called(1);

    MLY_ASSERT_LOCKED(sc);
    if ((error = mly_start(mc))) {
	return(error);
    }

    if (sc->mly_state & MLY_STATE_INTERRUPTS_ON) {
	/* sleep on the command */
	while(!(mc->mc_flags & MLY_CMD_COMPLETE)) {
	    mtx_sleep(mc, &sc->mly_lock, PRIBIO, "mlywait", 0);
	}
    } else {
	/* spin and collect status while we do */
	while(!(mc->mc_flags & MLY_CMD_COMPLETE)) {
	    mly_done(mc->mc_sc);
	}
    }
    return(0);
}