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
struct cdev {int dummy; } ;
struct amr_softc {int /*<<< orphan*/  amr_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_STATE_OPEN ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 struct amr_softc* devclass_get_softc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
amr_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
    int			unit = dev2unit(dev);
    struct amr_softc	*sc = devclass_get_softc(devclass_find("amr"), unit);

    debug_called(1);

    sc->amr_state |= AMR_STATE_OPEN;
    return(0);
}