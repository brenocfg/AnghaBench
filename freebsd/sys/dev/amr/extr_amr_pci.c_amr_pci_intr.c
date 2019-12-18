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
struct amr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amr_done (struct amr_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
amr_pci_intr(void *arg)
{
    struct amr_softc	*sc = (struct amr_softc *)arg;

    debug_called(3);

    /* collect finished commands, queue anything waiting */
    amr_done(sc);
}