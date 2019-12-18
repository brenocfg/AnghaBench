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
struct mly_user_command {scalar_t__ DataTransferLength; scalar_t__ RequestSenseLength; int /*<<< orphan*/  CommandStatus; int /*<<< orphan*/  RequestSenseBuffer; int /*<<< orphan*/  DataTransferBuffer; int /*<<< orphan*/  CommandMailbox; } ;
struct mly_softc {int /*<<< orphan*/  mly_lock; } ;
struct mly_command {scalar_t__ mc_length; int mc_flags; scalar_t__ mc_sense; scalar_t__ mc_resid; int /*<<< orphan*/ * mc_data; int /*<<< orphan*/  mc_status; int /*<<< orphan*/ * mc_packet; int /*<<< orphan*/ * mc_complete; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLY_CMD_COMPLETE ; 
 int MLY_CMD_DATAIN ; 
 int MLY_CMD_DATAOUT ; 
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ mly_alloc_command (struct mly_softc*,struct mly_command**) ; 
 int /*<<< orphan*/  mly_release_command (struct mly_command*) ; 
 int mly_start (struct mly_command*) ; 
 int /*<<< orphan*/  mtx_sleep (struct mly_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_user_command(struct mly_softc *sc, struct mly_user_command *uc)
{
    struct mly_command	*mc;
    int			error;

    /* allocate a command */
    MLY_LOCK(sc);
    if (mly_alloc_command(sc, &mc)) {
	MLY_UNLOCK(sc);
	return (ENOMEM);	/* XXX Linux version will wait for a command */
    }
    MLY_UNLOCK(sc);

    /* handle data size/direction */
    mc->mc_length = (uc->DataTransferLength >= 0) ? uc->DataTransferLength : -uc->DataTransferLength;
    if (mc->mc_length > 0) {
	if ((mc->mc_data = malloc(mc->mc_length, M_DEVBUF, M_NOWAIT)) == NULL) {
	    error = ENOMEM;
	    goto out;
	}
    }
    if (uc->DataTransferLength > 0) {
	mc->mc_flags |= MLY_CMD_DATAIN;
	bzero(mc->mc_data, mc->mc_length);
    }
    if (uc->DataTransferLength < 0) {
	mc->mc_flags |= MLY_CMD_DATAOUT;
	if ((error = copyin(uc->DataTransferBuffer, mc->mc_data, mc->mc_length)) != 0)
	    goto out;
    }

    /* copy the controller command */
    bcopy(&uc->CommandMailbox, mc->mc_packet, sizeof(uc->CommandMailbox));

    /* clear command completion handler so that we get woken up */
    mc->mc_complete = NULL;

    /* execute the command */
    MLY_LOCK(sc);
    if ((error = mly_start(mc)) != 0) {
	MLY_UNLOCK(sc);
	goto out;
    }
    while (!(mc->mc_flags & MLY_CMD_COMPLETE))
	mtx_sleep(mc, &sc->mly_lock, PRIBIO, "mlyioctl", 0);
    MLY_UNLOCK(sc);

    /* return the data to userspace */
    if (uc->DataTransferLength > 0)
	if ((error = copyout(mc->mc_data, uc->DataTransferBuffer, mc->mc_length)) != 0)
	    goto out;
    
    /* return the sense buffer to userspace */
    if ((uc->RequestSenseLength > 0) && (mc->mc_sense > 0)) {
	if ((error = copyout(mc->mc_packet, uc->RequestSenseBuffer, 
			     min(uc->RequestSenseLength, mc->mc_sense))) != 0)
	    goto out;
    }
    
    /* return command results to userspace (caller will copy out) */
    uc->DataTransferLength = mc->mc_resid;
    uc->RequestSenseLength = min(uc->RequestSenseLength, mc->mc_sense);
    uc->CommandStatus = mc->mc_status;
    error = 0;

 out:
    if (mc->mc_data != NULL)
	free(mc->mc_data, M_DEVBUF);
    MLY_LOCK(sc);
    mly_release_command(mc);
    MLY_UNLOCK(sc);
    return(error);
}