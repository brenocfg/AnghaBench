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
typedef  scalar_t__ u_int8_t ;
struct mly_softc {int /*<<< orphan*/ * mly_controllerparam; int /*<<< orphan*/ * mly_controllerinfo; } ;
struct mly_command_ioctl {int /*<<< orphan*/  sub_ioctl; } ;
typedef  int /*<<< orphan*/  mci ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MDACIOCTL_GETCONTROLLERINFO ; 
 int /*<<< orphan*/  MDACIOCTL_GETCONTROLLERPARAMETER ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bzero (struct mly_command_ioctl*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mly_ioctl (struct mly_softc*,struct mly_command_ioctl*,void**,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mly_get_controllerinfo(struct mly_softc *sc)
{
    struct mly_command_ioctl	mci;
    u_int8_t			status;
    int				error;

    debug_called(1);

    if (sc->mly_controllerinfo != NULL)
	free(sc->mly_controllerinfo, M_DEVBUF);

    /* build the getcontrollerinfo ioctl and send it */
    bzero(&mci, sizeof(mci));
    sc->mly_controllerinfo = NULL;
    mci.sub_ioctl = MDACIOCTL_GETCONTROLLERINFO;
    if ((error = mly_ioctl(sc, &mci, (void **)&sc->mly_controllerinfo, sizeof(*sc->mly_controllerinfo),
			   &status, NULL, NULL)))
	return(error);
    if (status != 0)
	return(EIO);

    if (sc->mly_controllerparam != NULL)
	free(sc->mly_controllerparam, M_DEVBUF);

    /* build the getcontrollerparameter ioctl and send it */
    bzero(&mci, sizeof(mci));
    sc->mly_controllerparam = NULL;
    mci.sub_ioctl = MDACIOCTL_GETCONTROLLERPARAMETER;
    if ((error = mly_ioctl(sc, &mci, (void **)&sc->mly_controllerparam, sizeof(*sc->mly_controllerparam),
			   &status, NULL, NULL)))
	return(error);
    if (status != 0)
	return(EIO);

    return(0);
}