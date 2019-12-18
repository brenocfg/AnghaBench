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
struct mly_user_health {int /*<<< orphan*/  HealthStatusBuffer; } ;
struct mly_softc {scalar_t__ mly_event_change; TYPE_2__* mly_mmbox; int /*<<< orphan*/  mly_lock; } ;
struct mly_health_status {scalar_t__ change_counter; } ;
typedef  int /*<<< orphan*/  mh ;
struct TYPE_3__ {struct mly_health_status status; } ;
struct TYPE_4__ {TYPE_1__ mmm_health; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 int PCATCH ; 
 int PRIBIO ; 
 int copyin (int /*<<< orphan*/ ,struct mly_health_status*,int) ; 
 int copyout (struct mly_health_status*,int /*<<< orphan*/ ,int) ; 
 int mtx_sleep (scalar_t__*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_user_health(struct mly_softc *sc, struct mly_user_health *uh)
{
    struct mly_health_status		mh;
    int					error;
    
    /* fetch the current health status from userspace */
    if ((error = copyin(uh->HealthStatusBuffer, &mh, sizeof(mh))) != 0)
	return(error);

    /* spin waiting for a status update */
    MLY_LOCK(sc);
    error = EWOULDBLOCK;
    while ((error != 0) && (sc->mly_event_change == mh.change_counter))
	error = mtx_sleep(&sc->mly_event_change, &sc->mly_lock, PRIBIO | PCATCH,
	    "mlyhealth", 0);
    mh = sc->mly_mmbox->mmm_health.status;
    MLY_UNLOCK(sc);
    
    /* copy the controller's health status buffer out */
    error = copyout(&mh, uh->HealthStatusBuffer, sizeof(mh));
    return(error);
}