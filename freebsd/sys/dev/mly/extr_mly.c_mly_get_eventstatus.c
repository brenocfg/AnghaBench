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
typedef  scalar_t__ u_int8_t ;
struct mly_softc {TYPE_2__* mly_mmbox; int /*<<< orphan*/  mly_event_counter; int /*<<< orphan*/  mly_event_waiting; int /*<<< orphan*/  mly_event_change; } ;
struct mly_health_status {int /*<<< orphan*/  next_event; int /*<<< orphan*/  change_counter; } ;
struct mly_command_ioctl {int /*<<< orphan*/  sub_ioctl; } ;
typedef  int /*<<< orphan*/  mci ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ mmm_health; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MDACIOCTL_GETHEALTHSTATUS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bcopy (struct mly_health_status*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct mly_command_ioctl*,int) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mly_health_status*,int /*<<< orphan*/ ) ; 
 int mly_ioctl (struct mly_softc*,struct mly_command_ioctl*,void**,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mly_get_eventstatus(struct mly_softc *sc)
{
    struct mly_command_ioctl	mci;
    struct mly_health_status	*mh;
    u_int8_t			status;
    int				error;

    /* build the gethealthstatus ioctl and send it */
    bzero(&mci, sizeof(mci));
    mh = NULL;
    mci.sub_ioctl = MDACIOCTL_GETHEALTHSTATUS;

    if ((error = mly_ioctl(sc, &mci, (void **)&mh, sizeof(*mh), &status, NULL, NULL)))
	return(error);
    if (status != 0)
	return(EIO);

    /* get the event counter */
    sc->mly_event_change = mh->change_counter;
    sc->mly_event_waiting = mh->next_event;
    sc->mly_event_counter = mh->next_event;

    /* save the health status into the memory mailbox */
    bcopy(mh, &sc->mly_mmbox->mmm_health.status, sizeof(*mh));

    debug(1, "initial change counter %d, event counter %d", mh->change_counter, mh->next_event);
    
    free(mh, M_DEVBUF);
    return(0);
}