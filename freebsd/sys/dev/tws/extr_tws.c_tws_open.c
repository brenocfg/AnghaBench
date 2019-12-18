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
struct tws_softc {int dummy; } ;
struct thread {int dummy; } ;
struct cdev {struct tws_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,struct cdev*,int) ; 

int
tws_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
    struct tws_softc *sc = dev->si_drv1;

    if ( sc ) 
        TWS_TRACE_DEBUG(sc, "entry", dev, oflags);
    return (0);
}