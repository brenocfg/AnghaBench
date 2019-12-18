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
struct TYPE_2__ {int /*<<< orphan*/ * ich_func; } ;
struct amr_softc {TYPE_1__ amr_ich; int /*<<< orphan*/  amr_state; int /*<<< orphan*/  amr_dev; struct amr_logdrive* amr_drive; } ;
struct amr_logdrive {int al_size; scalar_t__ al_disk; int al_heads; int al_sectors; int al_cylinders; } ;

/* Variables and functions */
 int AMR_MAXLD ; 
 int /*<<< orphan*/  AMR_STATE_INTEN ; 
 int /*<<< orphan*/  AMR_STATE_SHUTDOWN ; 
 scalar_t__ amr_query_controller (struct amr_softc*) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (scalar_t__,struct amr_logdrive*) ; 

__attribute__((used)) static void
amr_startup(void *arg)
{
    struct amr_softc	*sc = (struct amr_softc *)arg;
    struct amr_logdrive	*dr;
    int			i, error;
    
    debug_called(1);

    /* get up-to-date drive information */
    if (amr_query_controller(sc)) {
	device_printf(sc->amr_dev, "can't scan controller for drives\n");
	return;
    }

    /* iterate over available drives */
    for (i = 0, dr = &sc->amr_drive[0]; (i < AMR_MAXLD) && (dr->al_size != 0xffffffff); i++, dr++) {
	/* are we already attached to this drive? */
	if (dr->al_disk == 0) {
	    /* generate geometry information */
	    if (dr->al_size > 0x200000) {	/* extended translation? */
		dr->al_heads = 255;
		dr->al_sectors = 63;
	    } else {
		dr->al_heads = 64;
		dr->al_sectors = 32;
	    }
	    dr->al_cylinders = dr->al_size / (dr->al_heads * dr->al_sectors);
	    
	    dr->al_disk = device_add_child(sc->amr_dev, NULL, -1);
	    if (dr->al_disk == 0)
		device_printf(sc->amr_dev, "device_add_child failed\n");
	    device_set_ivars(dr->al_disk, dr);
	}
    }
    
    if ((error = bus_generic_attach(sc->amr_dev)) != 0)
	device_printf(sc->amr_dev, "bus_generic_attach returned %d\n", error);
    
    /* mark controller back up */
    sc->amr_state &= ~AMR_STATE_SHUTDOWN;

    /* interrupts will be enabled before we do anything more */
    sc->amr_state |= AMR_STATE_INTEN;

    /* pull ourselves off the intrhook chain */
    if (sc->amr_ich.ich_func)
	config_intrhook_disestablish(&sc->amr_ich);
    sc->amr_ich.ich_func = NULL;

    return;
}