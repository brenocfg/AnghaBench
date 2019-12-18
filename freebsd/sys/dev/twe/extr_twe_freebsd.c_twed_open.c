#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct twed_softc {TYPE_1__* twed_controller; } ;
struct disk {scalar_t__ d_drv1; } ;
struct TYPE_2__ {int twe_state; } ;

/* Variables and functions */
 int ENXIO ; 
 int TWE_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
twed_open(struct disk *dp)
{
    struct twed_softc	*sc = (struct twed_softc *)dp->d_drv1;

    debug_called(4);
	
    if (sc == NULL)
	return (ENXIO);

    /* check that the controller is up and running */
    if (sc->twed_controller->twe_state & TWE_STATE_SHUTDOWN)
	return(ENXIO);

    return (0);
}