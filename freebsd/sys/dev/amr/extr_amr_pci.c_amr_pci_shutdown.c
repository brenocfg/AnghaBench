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
struct amr_softc {TYPE_1__* amr_drive; int /*<<< orphan*/  amr_dev; int /*<<< orphan*/  amr_state; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ al_disk; } ;

/* Variables and functions */
 int AMR_MAXLD ; 
 int /*<<< orphan*/  AMR_STATE_SHUTDOWN ; 
 scalar_t__ amr_flush (struct amr_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct amr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
amr_pci_shutdown(device_t dev)
{
    struct amr_softc	*sc = device_get_softc(dev);
    int			i,error;

    debug_called(1);

    /* mark ourselves as in-shutdown */
    sc->amr_state |= AMR_STATE_SHUTDOWN;


    /* flush controller */
    device_printf(sc->amr_dev, "flushing cache...");
    printf("%s\n", amr_flush(sc) ? "failed" : "done");

    error = 0;

    /* delete all our child devices */
    for(i = 0 ; i < AMR_MAXLD; i++) {
	if( sc->amr_drive[i].al_disk != 0) {
	    if((error = device_delete_child(sc->amr_dev,sc->amr_drive[i].al_disk)) != 0)
		goto shutdown_out;
	    sc->amr_drive[i].al_disk = 0;
	}
    }

    /* XXX disable interrupts? */

shutdown_out:
    return(error);
}