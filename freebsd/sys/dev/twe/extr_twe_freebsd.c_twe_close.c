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
struct twe_softc {int /*<<< orphan*/  twe_state; } ;
struct thread {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_STATE_OPEN ; 

__attribute__((used)) static int
twe_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
    struct twe_softc		*sc = (struct twe_softc *)dev->si_drv1;

    TWE_IO_LOCK(sc);
    sc->twe_state &= ~TWE_STATE_OPEN;
    TWE_IO_UNLOCK(sc);
    return (0);
}