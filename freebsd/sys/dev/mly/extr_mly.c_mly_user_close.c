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
struct thread {int dummy; } ;
struct mly_softc {int /*<<< orphan*/  mly_state; } ;
struct cdev {struct mly_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_STATE_OPEN ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 

__attribute__((used)) static int
mly_user_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
    struct mly_softc	*sc = dev->si_drv1;

    MLY_LOCK(sc);
    sc->mly_state &= ~MLY_STATE_OPEN;
    MLY_UNLOCK(sc);
    return (0);
}