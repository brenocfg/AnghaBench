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
struct disk {scalar_t__ d_drv1; } ;
struct amrd_softc {TYPE_1__* amrd_controller; } ;
struct TYPE_2__ {int amr_state; } ;

/* Variables and functions */
 int AMR_STATE_SHUTDOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
amrd_open(struct disk *dp)
{
    struct amrd_softc	*sc = (struct amrd_softc *)dp->d_drv1;

    debug_called(1);

    if (sc == NULL)
	return (ENXIO);

    /* controller not active? */
    if (sc->amrd_controller->amr_state & AMR_STATE_SHUTDOWN)
	return(ENXIO);

    return (0);
}