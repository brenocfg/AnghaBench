#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_slices; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mxge_rem_msix_irqs (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_rem_single_irq (TYPE_1__*) ; 

__attribute__((used)) static void
mxge_rem_irq(mxge_softc_t *sc)
{
	if (sc->num_slices > 1)
		mxge_rem_msix_irqs(sc);
	else
		mxge_rem_single_irq(sc);
}