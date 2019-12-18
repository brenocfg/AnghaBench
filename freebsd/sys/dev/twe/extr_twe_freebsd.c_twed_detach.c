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
struct twed_softc {TYPE_1__* twed_disk; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int d_flags; } ;

/* Variables and functions */
 int DISKFLAG_OPEN ; 
 int EBUSY ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (TYPE_1__*) ; 

__attribute__((used)) static int
twed_detach(device_t dev)
{
    struct twed_softc *sc = (struct twed_softc *)device_get_softc(dev);

    debug_called(4);

    if (sc->twed_disk->d_flags & DISKFLAG_OPEN)
	return(EBUSY);

    disk_destroy(sc->twed_disk);

    return(0);
}