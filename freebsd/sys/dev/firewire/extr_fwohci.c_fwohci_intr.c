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
struct fwohci_softc {int /*<<< orphan*/  fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_GLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_GUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwohci_check_stat (struct fwohci_softc*) ; 

void
fwohci_intr(void *arg)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)arg;

	FW_GLOCK(&sc->fc);
	fwohci_check_stat(sc);
	FW_GUNLOCK(&sc->fc);
}