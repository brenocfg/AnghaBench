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
typedef  int u_int8_t ;
struct mly_softc {scalar_t__ mly_command_mailbox; scalar_t__ mly_error_status; int /*<<< orphan*/  mly_idbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 scalar_t__ MLY_ERROR_VALID (struct mly_softc*) ; 
 int MLY_GET_REG (struct mly_softc*,scalar_t__) ; 
 int /*<<< orphan*/  MLY_HM_STSACK ; 
 scalar_t__ MLY_IDBR_TRUE (struct mly_softc*,int /*<<< orphan*/ ) ; 
 int MLY_MSG_EMPTY ; 
#define  MLY_MSG_PARITY_ERROR 132 
#define  MLY_MSG_RACE_IN_PROGRESS 131 
#define  MLY_MSG_RACE_ON_CRITICAL 130 
#define  MLY_MSG_RACE_RECOVERY_FAIL 129 
#define  MLY_MSG_SPINUP 128 
 int /*<<< orphan*/  MLY_SET_REG (struct mly_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_printf (struct mly_softc*,char*,...) ; 

__attribute__((used)) static int
mly_fwhandshake(struct mly_softc *sc) 
{
    u_int8_t	error, param0, param1;
    int		spinup = 0;

    debug_called(1);

    /* set HM_STSACK and let the firmware initialise */
    MLY_SET_REG(sc, sc->mly_idbr, MLY_HM_STSACK);
    DELAY(1000);	/* too short? */

    /* if HM_STSACK is still true, the controller is initialising */
    if (!MLY_IDBR_TRUE(sc, MLY_HM_STSACK))
	return(0);
    mly_printf(sc, "controller initialisation started\n");

    /* spin waiting for initialisation to finish, or for a message to be delivered */
    while (MLY_IDBR_TRUE(sc, MLY_HM_STSACK)) {
	/* check for a message */
	if (MLY_ERROR_VALID(sc)) {
	    error = MLY_GET_REG(sc, sc->mly_error_status) & ~MLY_MSG_EMPTY;
	    param0 = MLY_GET_REG(sc, sc->mly_command_mailbox);
	    param1 = MLY_GET_REG(sc, sc->mly_command_mailbox + 1);

	    switch(error) {
	    case MLY_MSG_SPINUP:
		if (!spinup) {
		    mly_printf(sc, "drive spinup in progress\n");
		    spinup = 1;			/* only print this once (should print drive being spun?) */
		}
		break;
	    case MLY_MSG_RACE_RECOVERY_FAIL:
		mly_printf(sc, "mirror race recovery failed, one or more drives offline\n");
		break;
	    case MLY_MSG_RACE_IN_PROGRESS:
		mly_printf(sc, "mirror race recovery in progress\n");
		break;
	    case MLY_MSG_RACE_ON_CRITICAL:
		mly_printf(sc, "mirror race recovery on a critical drive\n");
		break;
	    case MLY_MSG_PARITY_ERROR:
		mly_printf(sc, "FATAL MEMORY PARITY ERROR\n");
		return(ENXIO);
	    default:
		mly_printf(sc, "unknown initialisation code 0x%x\n", error);
	    }
	}
    }
    return(0);
}