#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_slices; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int mxge_add_msix_irqs (TYPE_1__*) ; 
 int mxge_add_single_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_rem_msix_irqs (TYPE_1__*) ; 

__attribute__((used)) static int
mxge_add_irq(mxge_softc_t *sc)
{
	int err;

	if (sc->num_slices > 1)
		err = mxge_add_msix_irqs(sc);
	else
		err = mxge_add_single_irq(sc);
	
	if (0 && err == 0 && sc->num_slices > 1) {
		mxge_rem_msix_irqs(sc);
		err = mxge_add_msix_irqs(sc);
	}
	return err;
}