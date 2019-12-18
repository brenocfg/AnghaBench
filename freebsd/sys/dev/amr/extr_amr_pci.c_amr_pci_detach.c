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
struct amr_softc {int amr_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AMR_STATE_OPEN ; 
 int EBUSY ; 
 int /*<<< orphan*/  amr_pci_free (struct amr_softc*) ; 
 int amr_pci_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct amr_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amr_pci_detach(device_t dev)
{
    struct amr_softc	*sc = device_get_softc(dev);
    int			error;

    debug_called(1);

    if (sc->amr_state & AMR_STATE_OPEN)
	return(EBUSY);

    if ((error = amr_pci_shutdown(dev)))
	return(error);

    amr_pci_free(sc);

    return(0);
}